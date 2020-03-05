#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Component.hpp"
#include "ShaderProgram.hpp"
#include "VAO.hpp"

//when a chunk object is made update and create a VAO
//then when a chunk is destroyed free the GPU memory
//manage the object renderer ?
class Chunk : public Engine::Component {
private:
    glm::vec3 position;
    unsigned int size;
    Engine::VAO* m_vao = NULL;
    Engine::ShaderProgram* terrainShader;
    //create the shader programs if this is the first instantiation
    static bool first;
    //populate these once
    static Engine::ShaderProgram* genDensities;
    static Engine::ShaderProgram* genFilledCells;
    static Engine::ShaderProgram* genVertMarkers;
    static Engine::ShaderProgram* genVerts;
    static Engine::ShaderProgram* splatIndices;
    static Engine::ShaderProgram* genIndices;
    
    //populate the VAO of the chunk
    void updateChunk();

    GLuint createDensityTex();
public:
    Chunk(glm::vec3 _position, unsigned int size, Engine::ShaderProgram* _terrainShader);
    virtual ~Chunk(){};

    virtual void start();
};
