#include "Renderables/TileChunkRenderable.hpp"

#include <iostream>

#include "Components/Transform.hpp"



TileChunkRenderable::TileChunkRenderable()
    : Renderable() {
}

TileChunkRenderable::TileChunkRenderable(VAO* _vao)
    : Renderable() {
    vao = _vao;
    shaderProgram = new ShaderProgram("../Shaders/TileChunk/vert.glsl",
                                      "../Shaders/TileChunk/frag.glsl");
}

void TileChunkRenderable::render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix){
    if(isShown){
        //std::cout << "Rendering: " << object->getName() << std::endl;
        glm::mat4 newModelMatrix = ((Transform*)object->getComponent("transform"))->calcModelMatrix();
        shaderProgram->start();

        shaderProgram->setUniformMat4(newModelMatrix,"M");
        shaderProgram->setUniformMat4(viewMatrix,"V");
        shaderProgram->setUniformMat4(projectionMatrix,"P");

        vao->draw();
    }
}
