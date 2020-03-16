#pragma once

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "Components/Renderable.hpp"
#include "Components/Transform.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace Engine {

class SimpleRenderable : public Renderable {
private:
    glm::vec3 color = glm::vec3(1, 1, 1);
public:
    SimpleRenderable()
        : Renderable() {
    }

    SimpleRenderable(VAO* _vao)
        : Renderable() {
        vao = _vao;
        shaderProgram = new ShaderProgram("../Engine/Shaders/Simple/vert.glsl",
                                          "../Engine/Shaders/Simple/frag.glsl");
    }

    virtual void draw(){
        if(isShown){
            //std::cout << "Rendering: " << object->getName() << std::endl;
            glm::mat4 newModelMatrix = entity->getComponent<Transform>().calcModelMatrix();
            shaderProgram->start();

            shaderProgram->setUniformVec3(color, "c");
            shaderProgram->setUniformMat4(newModelMatrix,"M");

            vao->draw();
        }
    }

    void setColor(float r, float g, float b){
        color = glm::vec3(r, g, b);
    }
};

}
