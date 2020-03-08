#pragma once

//opengl includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "stb_image.h"

class Texture2D {
public:
    Texture2D(const char* path);
    void bind();
private:
};
