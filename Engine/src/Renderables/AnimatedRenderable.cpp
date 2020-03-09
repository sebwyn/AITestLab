#include "Renderables/AnimatedRenderable.hpp"

#include <iostream>

#include "Components/Transform.hpp"

using namespace Engine;


AnimatedRenderable::AnimatedRenderable()
    : Renderable() {
}

AnimatedRenderable::AnimatedRenderable(VAO* _vao)
    : Renderable() {
    vao = _vao;
    shaderProgram = new ShaderProgram("../../Engine/Shaders/Animated/vert.glsl",
                                      "../../Engine/Shaders/Simple/frag.glsl");
}

void AnimatedRenderable::render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix){
    if(isShown){
        //std::cout << "Rendering: " << object->getName() << std::endl;
        glm::mat4 newModelMatrix = ((Transform*)object->getComponent("transform"))->calcModelMatrix();
        shaderProgram->start();
        if(bones.size() > 0){
            shaderProgram->setUniformMat4Array(bones, "boneTransforms");
        }
        shaderProgram->setUniformMat4(newModelMatrix,"M");
        shaderProgram->setUniformMat4(viewMatrix,"V");
        shaderProgram->setUniformMat4(projectionMatrix,"P");
        vao->draw();
    }
}
