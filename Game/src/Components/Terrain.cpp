#include "Terrain.hpp"

#include "GameObject.hpp"

Terrain::Terrain(Engine::ShaderProgram* program)
 : Component("terrain"), terrainShader(program)  {}

void Terrain::start(){
    Engine::GameObject* chunk = new Engine::GameObject("chunk", true);
    chunk->attachComponent(new Chunk(glm::vec3(0, 0, 0), 32, terrainShader));
    object->addChild(chunk);
}
