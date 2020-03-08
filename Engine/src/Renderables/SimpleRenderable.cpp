#include "Renderables/SimpleRenderable.hpp"

#include <iostream>

#include "Components/Transform.hpp"

using namespace Engine;


SimpleRenderable::SimpleRenderable()
    : Renderable() {
}

SimpleRenderable::SimpleRenderable(VAO* _vao)
    : Renderable() {
    vao = _vao;
    shaderProgram = new ShaderProgram("../../Engine/Shaders/Simple/vert.glsl",
                                      "../../Engine/Shaders/Simple/frag.glsl");
}

void SimpleRenderable::render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix){
    if(isShown){
        //std::cout << "Rendering: " << object->getName() << std::endl;
        glm::mat4 newModelMatrix = ((Transform*)object->getComponent("transform"))->calcModelMatrix();
        shaderProgram->start();

        shaderProgram->setUniformVec3(color, "c");
        shaderProgram->setUniformMat4(newModelMatrix,"M");
        shaderProgram->setUniformMat4(viewMatrix,"V");
        shaderProgram->setUniformMat4(projectionMatrix,"P");

        vao->draw();
    }
}

void SimpleRenderable::setColor(float r, float g, float b){
    color = glm::vec3(r, g, b);
}
