#include "Components/Camera.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>


using namespace Engine;

Camera::Camera(float _width, float _height)
 : Component(std::string("camera")) {

    FOV = 90;
    width = _width;
    height = _height;
    lookAtState = lookAtMode::DISABLED;
    viewDirection = glm::vec3(0,0,1);
    isOrtho = false;

}

void Camera::setFOV(float fov){
    FOV = fov;

    updateProjectionMatrix();
}

void Camera::updateAspect(float _width, float _height){
    width = _width;
    height = _height;

    updateProjectionMatrix();
}

void Camera::start(){
    //lateUpdate();
}

void Camera::lateUpdate(){
    updateLookAt();
    updateViewMatrix();
}

void Camera::updateLookAt(){
    glm::vec3 target;
    glm::vec3 position = object->transform->calcGlobalPosition();
    switch (lookAtState){
        case lookAtMode::POINT:
            viewDirection = glm::normalize(targetPoint-position);
            break;
        case lookAtMode::OBJECT:
            target = targetObject->transform->calcGlobalPosition();
            viewDirection = glm::normalize(target-position);
            break;
        case lookAtMode::DISABLED:
            viewDirection = object->transform->getForward();
            break;
    }
}

void Camera::lookAt(GameObject* _object){
    lookAtState = lookAtMode::OBJECT;
    targetObject = _object;
}

void Camera::lookAt(float x, float y, float z){
    lookAtState = lookAtMode::POINT;
    targetPoint = glm::vec3(x,y,z);
}

void Camera::disableLookAt(){
    lookAtState = lookAtMode::DISABLED;
}

void Camera::updateViewMatrix(){
    glm::vec3 position = object->transform->calcGlobalPosition();
    viewMatrix = glm::lookAt(position,
                                    position+viewDirection,
                                    glm::vec3(0,1,0));
}

void Camera::updateProjectionMatrix(){
    if (isOrtho) {
        projectionMatrix = glm::ortho(0.0f,width,
                                      0.0f,height,
                                      -1.0f,10000.0f);
    }else{
        projectionMatrix = glm::perspective(glm::radians(FOV),
                                            width / height,
                                            0.1f,
                                            10000.0f);
    }
}

void Camera::ortho(){
    isOrtho = true;

    updateProjectionMatrix();
}

void Camera::perspective(){
    isOrtho = false;

    updateProjectionMatrix();
}
