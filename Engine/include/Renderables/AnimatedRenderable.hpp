#pragma once

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "Component.hpp"

#include "Components/Renderable.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace Engine {

class AnimatedRenderable : public Renderable {
public:
    AnimatedRenderable();
    AnimatedRenderable(VAO* _vao);

    virtual void render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

	inline void setBoneTransforms(std::vector<glm::mat4> _bones){bones = _bones;}
private:

	std::vector<glm::mat4> bones = std::vector<glm::mat4>(0);
};

}
