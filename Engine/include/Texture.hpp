#pragma once

//opengl includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Texture {
public:
    Texture(const char* path);
    ~Texture();

    void bind(int index);

    int getWidth();
    int getHeight();

private:
    unsigned int texture;
    int width, height, nrChannels;
};
