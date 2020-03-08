#pragma once

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "Component.hpp"

#include "Components/Renderable.hpp"

#include <vector>
#include <glm/glm.hpp>

using namespace Engine;

class TileChunkRenderable : public Renderable {
public:
    TileChunkRenderable();
    TileChunkRenderable(VAO* _vao);

    virtual void render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

private:


};
