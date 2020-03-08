#pragma once

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "Component.hpp"

#include "Components/Renderable.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace Engine {

class SimpleRenderable : public Renderable {
public:
    SimpleRenderable();
    SimpleRenderable(VAO* _vao);

    virtual void render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

    void setColor(float r, float g, float b);
private:

    //rendering vars (later this will probably be a material)
    glm::vec3 color = glm::vec3(1, 1, 1);
};

}
