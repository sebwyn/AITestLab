#pragma once

#include "ECS.hpp"

#include "ShaderProgram.hpp"
#include "VAO.hpp"

namespace Engine {

class Renderable : public Component {
protected:
    bool isShown = true;

    VAO* vao;
    ShaderProgram* shaderProgram;
public:
    Renderable() = default;

    Renderable(VAO* _vao, ShaderProgram* _program) 
        : vao(_vao), shaderProgram(_program) {}

    virtual ~Renderable(){}

    inline void setVAO(VAO* _vao) {vao = _vao;};

    inline bool getShown() const {return isShown;}
    inline void setShown(bool state){isShown = state;}
};

}

