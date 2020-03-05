#pragma once

#include "PerlinNoise.h"

#include "Component.hpp"
#include "VAO.hpp"
#include "Renderable.hpp"

//for debugging
#include "GameObject.hpp"

class oTerrain : public Engine::Component {
public:
    oTerrain(glm::ivec3 _dimensions,float resolution,Engine::ShaderProgram* prog, Engine::GameObject* _root, float _s);

    virtual void start();
private:
    float s;

    void generate();
    float generator(glm::vec3 p);
    float lerp(float a, float b, float p);

    void march(); 
    
    int indexFromVec3(int x, int y, int z);
    glm::vec3 interp(glm::vec4 a, glm::vec4 b);
    glm::vec3 makeNormal(glm::vec3 uvw);

    std::vector<glm::vec4> points; 
    
    PerlinNoise perlin1;
    PerlinNoise perlin2;
    PerlinNoise perlin3;
    PerlinNoise perlin4;
    PerlinNoise perlin5;
    PerlinNoise perlin6;
    PerlinNoise perlin7;

    unsigned int seed;
    unsigned int lastNoise = 0;

    float isoLevel;

    glm::ivec3 dimensions;
    float resolution;
    
    Engine::ShaderProgram* program;
    Engine::VAO* mesh;
    Engine::Renderable* renderable;
    
    //for debugging purposes
    Engine::GameObject* root;

    static const int triangulation[256][16];
    static const int cornerIndexAFromEdge[12];
    static const int cornerIndexBFromEdge[12];
    static const glm::vec3 cornerPosFromIndex[8];
};
