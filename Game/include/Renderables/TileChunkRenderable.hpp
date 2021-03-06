#pragma once

#include "ShaderProgram.hpp"
#include "VAO.hpp"
#include "Texture.hpp"

#include "Component.hpp"

#include "Components/Renderable.hpp"

#include <vector>
#include <glm/glm.hpp>

using namespace Engine;

class TileChunkRenderable : public Renderable {
public:
    TileChunkRenderable();
    TileChunkRenderable(VAO* _vao);

    ~TileChunkRenderable();


    virtual void render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

    void addTexture(Texture* tex);

    void setSheetSize(int w, int h);
    void setTile(int x, int y);

private:
    glm::vec2 tileSize;
    glm::ivec2 tile;
    Texture* texture;
};
