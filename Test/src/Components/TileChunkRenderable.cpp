#include "Components/TileChunkRenderable.hpp"

#include <iostream>

#include "Components/Transform.hpp"



TileChunkRenderable::TileChunkRenderable()
    : Renderable() {
}

TileChunkRenderable::TileChunkRenderable(VAO* _vao)
    : Renderable() {
    vao = _vao;
    shaderProgram = new ShaderProgram("Shaders/TileChunk/vert.glsl",
                                      "Shaders/TileChunk/frag.glsl");

}

TileChunkRenderable::~TileChunkRenderable(){
}

void TileChunkRenderable::setMatrices(glm::mat4 p, glm::mat4 v){
    projectionMatrix = p;
    viewMatrix = v;
}

void TileChunkRenderable::draw(){
    if(isShown){
        glm::mat4 newModelMatrix = entity->getComponent<Transform>().calcModelMatrix();
        shaderProgram->start();

        shaderProgram->setUniformInt(0,"texture1");
        shaderProgram->setUniformVec2(tileSize,"tileSize");
        shaderProgram->setUniformVec2(tile,"tile");

        shaderProgram->setUniformMat4(newModelMatrix,"M");
        shaderProgram->setUniformMat4(viewMatrix,"V");
        shaderProgram->setUniformMat4(projectionMatrix,"P");

        texture->bind(0);

        vao->draw();
    }
}

void TileChunkRenderable::addTexture(Texture* tex){
    texture = tex;
}

void TileChunkRenderable::setSheetSize(int w, int h){
    tileSize = glm::vec2(1/(float)w,1/(float)h);
}

void TileChunkRenderable::setTile(int x, int y){
    tile = glm::ivec2(x,y);
}
