#include "Components/Renderable.hpp"

#include <iostream>

#include "Components/Transform.hpp"

using namespace Engine;

Renderable::Renderable()
 : Component("renderable") {
    isShown = true;
}

Renderable::Renderable(VAO* _vao, ShaderProgram* _program) : Component("renderable") {
    isShown = true;
    vao = _vao;
    shaderProgram = _program;
}

void Renderable::setVAO(VAO* _vao){
    vao = _vao;
}
/*
void Renderable::createShader(const char* vPath, const char* fPath){
    shaderProgram = new ShaderProgram(vPath,fPath);
}
*/
