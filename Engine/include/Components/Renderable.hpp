#pragma once

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "Component.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace Engine {

class Renderable : public Component {
public:
    Renderable();
    Renderable(VAO* _vao, ShaderProgram* _program);
    virtual ~Renderable(){}

    void setVAO(VAO* _vao);
    void setShaderProgram(ShaderProgram* program);

    virtual void render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {return;};

    inline bool getShown() const {return isShown;}
    void setShown(bool state){isShown = state;}

protected:
    bool isShown;

    VAO* vao;
    ShaderProgram* shaderProgram;
};

}
