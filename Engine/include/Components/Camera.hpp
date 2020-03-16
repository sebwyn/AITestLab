#pragma once

#include <glm/glm.hpp>

#include "ECS.hpp"

#include "Components/Transform.hpp"

namespace Engine {

class Camera : public Component {
private:
    enum lookAtMode {
        DISABLED,
        POINT,
        ENTITY
    };
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 viewDirection = glm::vec3(0,0,1);
    glm::vec3 targetPoint;
    Entity* targetEntity;
    lookAtMode lookAtState = lookAtMode::DISABLED;
    float FOV = 90;
    bool isOrtho = false;

    float width, height;
public:
    Camera(float _width, float _height)
        : width(_width), height(_height){};

    void setFOV(float fov);
    void updateAspect(float _width, float _height);

    void lookAt(Entity* entity);
    void lookAt(float x, float y, float z);
    void disableLookAt();

    void ortho();
    void perspective();

    virtual void init();
    virtual void update();

    inline glm::vec3 getViewDirection() const {return viewDirection;};
    inline glm::mat4 getProjectionMatrix() const {return projectionMatrix;};
    inline glm::mat4 getViewMatrix() const {return viewMatrix;};
    inline float getWidth() const {return width;};
    inline float getHeight() const {return height;};
private:
    void updateViewMatrix();
    void updateProjectionMatrix();

    void updateLookAt();
};

}
