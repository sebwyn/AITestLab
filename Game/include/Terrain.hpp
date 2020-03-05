#pragma once

#include <vector>

#include "ShaderProgram.hpp"
#include "Component.hpp"
#include "Chunk.hpp"

class Terrain : public Engine::Component {
private:
    Engine::ShaderProgram* terrainShader;
public:
    Terrain(Engine::ShaderProgram* program);
    virtual ~Terrain(){};

    virtual void start(); 
};
