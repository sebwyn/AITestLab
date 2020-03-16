#pragma once

#include "ECS.hpp"
#include "WindowEventManager.hpp"
#include "Components/Transform.hpp"
#include "Components/Camera.hpp"
#include <glm/glm.hpp>

using namespace glm;
using namespace Engine;

class FirstPersonController : public Component, public WindowEventSubscriber{
private:

    float speed = 1;
    float mouseSpeed = 0.3;

    float lastTime = 0;

    vec2 rotate = vec2(0,0);
    vec3 move = vec3(0,0,0);

    vec3 translationVector = vec3(0,0,0);
    vec2 rotationVector = vec2(0,180);
public:
    FirstPersonController();

    virtual void init();
    virtual void update();

private:
    virtual void onKey(int key, int scancode, int action, int mods);
    virtual void onCursorMove(double xpos, double ypos);

    void calcTranslation(float dt);
    void calcRotation(float dt);
};
