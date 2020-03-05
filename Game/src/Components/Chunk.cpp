#include "Chunk.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

#include "DebugRenderable.hpp"
#include "Renderable.hpp"

bool Chunk::first = true;
//shader programs dec here
Engine::ShaderProgram* Chunk::genDensities;
Engine::ShaderProgram* Chunk::genFilledCells;
Engine::ShaderProgram* Chunk::genVertMarkers;
Engine::ShaderProgram* Chunk::genVerts;
Engine::ShaderProgram* Chunk::splatIndices;
Engine::ShaderProgram* Chunk::genIndices;


Chunk::Chunk(glm::vec3 _position, unsigned int _size, Engine::ShaderProgram* _terrainShader)
 : Component("chunk"), position(_position), size(_size), terrainShader(_terrainShader) {
    if(first){
        first = false;
        genDensities = new Engine::ShaderProgram("../Shaders/genDensities.vs", "../Shaders/genDensities.gs", "../Shaders/genDensities.fs");
        const char* filledCellsTF[] = {"oxyzc"};
        genFilledCells = new Engine::ShaderProgram("../Shaders/genFilledCells.vs", "../Shaders/genFilledCells.gs", "../Shaders/empty.fs", 1, filledCellsTF);
        const char* vertMarkersTF[] = {"x8_y8_z8_null4_edge4"};
        genVertMarkers = new Engine::ShaderProgram("../Shaders/genVertMarkers.vs", "../Shaders/genVertMarkers.gs", "../Shaders/empty.fs", 1, vertMarkersTF);
        const char* vertsTF[] = {"position", "normal"};
        genVerts = new Engine::ShaderProgram("../Shaders/genVerts.vs", "../Shaders/genVerts.gs", "../Shaders/empty.fs", 2, vertsTF);
        //DEBUG FEEDBACK
        const char* df[]  = {"pos"};
        splatIndices = new Engine::ShaderProgram("../Shaders/splatVertID.vs", "../Shaders/splatVertID.gs", "../Shaders/splatVertID.fs", 1, df);
        const char* indicesTF[] = {"index"};
        genIndices = new Engine::ShaderProgram("../Shaders/genIndices.vs", "../Shaders/genIndices.gs", "../Shaders/empty.fs", 1, indicesTF);
    }
}

void Chunk::start(){
    //populate m_vao
    updateChunk();
    object->attachComponent(new Engine::Renderable(m_vao, terrainShader));
}

//TO DO: resize verts to use less VRAM
void Chunk::updateChunk(){
    
    unsigned int csp1 = size + 1;
    unsigned int csp2 = csp1+1;
    //set appropriate shader uniforms
   
    GLuint densityTexture = createDensityTex();
    //cleanup densities

    //begin compute
    glEnable(GL_RASTERIZER_DISCARD);

    //generate filled cells
    GLuint filledCells;
    glGenBuffers(1, &filledCells);
    glBindBuffer(GL_ARRAY_BUFFER, filledCells);
    glBufferData(GL_ARRAY_BUFFER,csp1*csp1*csp1*sizeof(GLuint),NULL,GL_STATIC_READ);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    GLuint filledCellsFeedback;
    glGenTransformFeedbacks(1, &filledCellsFeedback);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, filledCellsFeedback);

    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, filledCells);
    genFilledCells->start();
    genFilledCells->setUniformInt(size, "chunkSize");
    
    //pass textures to draw
    Engine::VAO emptyVao = Engine::VAO();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, densityTexture);

    GLuint cellSizeQuery;
    glGenQueries(1, &cellSizeQuery);
    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, cellSizeQuery);
    
    glBeginTransformFeedback(GL_POINTS);
    //capture a point for every voxel
    emptyVao.bind();
    glDrawArraysInstanced(GL_POINTS, 0, csp1*csp1, csp1);
    emptyVao.unbind();
    
    glFlush();
    glEndTransformFeedback();
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);

    unsigned int numCells = 0;
    glGetQueryObjectuiv(cellSizeQuery, GL_QUERY_RESULT, &numCells);
    
    //DEBUG PRINT:
    std::cout << numCells << std::endl;
    /*
    unsigned int filledCellsData[numCells];
    glBindBuffer(GL_ARRAY_BUFFER, filledCells);
    glGetBufferSubData(GL_ARRAY_BUFFER,0,numCells*sizeof(GLuint), filledCellsData);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::cout << "Filled Cells: " << std::hex;
    for(int i = 0; i < numCells; i++){
        std::cout << filledCellsData[i] << " ";
    }
    std::cout << std::dec << std::endl;
    */
    
    //generate vertex marker list (sparse list of vertices)
    GLuint vertMarkerFeedback;
    glGenTransformFeedbacks(1, &vertMarkerFeedback);
    
    GLuint vertMarkers;
    glGenBuffers(1, &vertMarkers);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertMarkers);
    glBufferData(GL_ARRAY_BUFFER,3*numCells*sizeof(GLuint),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, vertMarkerFeedback);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vertMarkers);
    
    Engine::VAO cellsVao = Engine::VAO();
    cellsVao.addGLIntBuffer(0, filledCells, numCells, 1);

    genVertMarkers->start();
    //no uniforms

    glBeginTransformFeedback(GL_POINTS);
    //set the attributes for the draw call
    cellsVao.bind();
    cellsVao.enableAttribs();
    glDrawTransformFeedback(GL_POINTS, filledCellsFeedback);
    cellsVao.disableAttribs();
    cellsVao.unbind();
    glEndTransformFeedback();
    
    glFlush();
    
    glDisable(GL_RASTERIZER_DISCARD);

    //DEBUG
    glFlush();
    /* 
    unsigned int vertMarkersData[3*numCells];
    
    glBindBuffer(GL_ARRAY_BUFFER, vertMarkers);
    glGetBufferSubData(GL_ARRAY_BUFFER,0,3*numCells*sizeof(GLuint),vertMarkersData);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    std::cout << "VertMarkers: " << std::hex;
    for(int i = 0; i < 1000; i++){
        std::cout << vertMarkersData[i] << " ";
    }
    std::cout << std::dec << std::endl;
    
    glDisable(GL_RASTERIZER_DISCARD);
    */
    
    //generate complete vertices
    //ideally to conserve memory these buffers should of size numVertMarkers*3
    GLuint vertPositions;
    glGenBuffers(1, &vertPositions);
    GLuint vertNormals;
    glGenBuffers(1, &vertNormals);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertPositions);
    glBufferData(GL_ARRAY_BUFFER,3*3*numCells*sizeof(GLfloat),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER, vertNormals);
    glBufferData(GL_ARRAY_BUFFER,3*3*numCells*sizeof(GLfloat),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vertPositions);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, vertNormals);
    genVerts->start();
    genVerts->setUniformInt(size, "chunkSize");

    Engine::VAO vertMarkersVao = Engine::VAO();
    vertMarkersVao.addGLIntBuffer(0, vertMarkers, numCells*3, 1);

    glBeginTransformFeedback(GL_POINTS);
    //Transform Feedback 
    vertMarkersVao.bind();
    vertMarkersVao.enableAttribs();
    glDrawTransformFeedback(GL_POINTS, vertMarkerFeedback);
    vertMarkersVao.disableAttribs();
    vertMarkersVao.unbind();
    
    glEndTransformFeedback();
    
    //DEBUG:
    glFlush();
    /* 
    float vertData[3*3*numCells];

    glBindBuffer(GL_ARRAY_BUFFER, vertPositions);
    glGetBufferSubData(GL_ARRAY_BUFFER,0,3*3*numCells*sizeof(GLfloat),vertData);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::cout << "verts: ";
    for(int i = 0; i < 50; i+=3){
        std::cout << "(" << vertData[i] << ", " << vertData[i+1] << ", " << vertData[i+2] << ") "; 
    }
    std::cout << std::endl;
    */
    //splat verts
    glDisable(GL_RASTERIZER_DISCARD);
    
    GLuint indiceTexture;
    glGenTextures(1, &indiceTexture);

    glBindTexture(GL_TEXTURE_3D, indiceTexture);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_R32UI, csp1*3, csp1, csp1, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_3D, 0);

    GLuint indiceFramebuffer;
    glGenFramebuffers(1, &indiceFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, indiceFramebuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,  indiceTexture, 0);

    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0}; 
    glDrawBuffers(1, drawBuffers);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "rut roh" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, indiceFramebuffer);
    //glClearColor(1.0, 1.0, 1.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    splatIndices->start();
    splatIndices->setUniformInt(csp1, "chunkSize");
    
    vertMarkersVao.bind();
    vertMarkersVao.enableAttribs();
    //draw a point for output of vertMarkerFeedback
    glViewport(0, 0, csp1*3, csp1);
    glDrawTransformFeedback(GL_POINTS, vertMarkerFeedback);
    vertMarkersVao.disableAttribs();
    vertMarkersVao.unbind();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //DEBUG
    glFlush();
     
    unsigned int indicePixels[csp1*3*csp1*csp1];
    memset(indicePixels, 0, csp1*3*csp1*csp1*sizeof(unsigned int));

    glBindTexture(GL_TEXTURE_3D, indiceTexture);
    glGetTexImage(GL_TEXTURE_3D, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, indicePixels);
    glBindTexture(GL_TEXTURE_3D, 0);
    
    std::cout << "pixels: ";
    for(int i = 0; i < 100; i++){
        std::cout << indicePixels[i] << " ";
    }
    std::cout << "\n";
    
    //gen indices (compute)
    glEnable(GL_RASTERIZER_DISCARD);
    
    GLuint indices;
    glGenBuffers(1, &indices);

    glBindBuffer(GL_ARRAY_BUFFER, indices);
    glBufferData(GL_ARRAY_BUFFER,15*numCells*sizeof(GLuint),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, indices);
    genIndices->start();
    //pass indice texture to compute
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, indiceTexture);
    
    GLuint indiceSizeQuery;
    glGenQueries(1, &indiceSizeQuery);
    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, indiceSizeQuery);
    
    glBeginTransformFeedback(GL_POINTS);
    cellsVao.bind();
    cellsVao.enableAttribs();
    glDrawTransformFeedback(GL_POINTS, filledCellsFeedback);
    cellsVao.disableAttribs();
    cellsVao.unbind();
    glEndTransformFeedback();
    
    glFlush();
    
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    unsigned int numIndices;
    glGetQueryObjectuiv(indiceSizeQuery, GL_QUERY_RESULT, &numIndices);
    
    //return to normal
    glDisable(GL_RASTERIZER_DISCARD);
    //DEBUG PRINT:
    std::cout << numIndices << std::endl;

    unsigned int cpuIndices[10];
    
    glBindBuffer(GL_ARRAY_BUFFER, indices);
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, 10*sizeof(GLuint), cpuIndices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for(int i = 0; i < 10; i++){
        std::cout << "index: " << cpuIndices[i] << std::endl;
    }

    //DEBUG:
    Engine::GameObject* debugDense = new Engine::GameObject("debugDensity", true);
    debugDense->attachComponent(new DebugRenderable(densityTexture, genDensities));
    object->addChild(debugDense);
    
    /*
    if(m_vao != NULL){
        delete m_vao;
    }
    m_vao = new Engine::VAO();
    m_vao->addGLFloatBuffer(0, vertPositions, 3*numCells, 3);
    m_vao->addGLFloatBuffer(1, vertNormals, 3*numCells, 3);
    m_vao->addGLElementBuffer(indices, numIndices);
    */
    m_vao = new Engine::VAO();
}

GLuint Chunk::createDensityTex(){
    unsigned int csp1 = size + 1;
    unsigned int csp2 = csp1+1;
    
    GLuint densityTexture;
    glGenTextures(1, &densityTexture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, densityTexture);
    
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, csp2, csp2, csp2, 0, GL_RED, GL_FLOAT, NULL);
    //set the sampling to linear (useful for calculating gradient)
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_3D, 0);

    //create the framebuffer
    GLuint densityFramebuffer;
    glGenFramebuffers(1, &densityFramebuffer);
    
    glBindFramebuffer(GL_FRAMEBUFFER, densityFramebuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, densityTexture, 0);
    
    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "rut roh" << std::endl;
    }

    //render
    glBindFramebuffer(GL_FRAMEBUFFER, densityFramebuffer);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    genDensities->start();
    genDensities->setUniformInt(size, "chunkSize");
    genDensities->setUniformVec3(position, "chunkPos");

    Engine::VAO emptyVao = Engine::VAO();
    emptyVao.bind();
    
    glViewport(0, 0, csp2, csp2);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, csp2);
    
    emptyVao.unbind();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //do some cleanup
    //note: the vao should clean itself up
    glDeleteFramebuffers(1, &densityFramebuffer);

    glFlush();

    return densityTexture;
}
