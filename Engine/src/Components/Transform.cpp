#include "Components/Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>

using namespace Engine;

Transform::Transform(GameObject* _object){
     object = _object;
     position = glm::vec3(0, 0, 0);
     rotation = glm::vec3(0, 0, 0);
     size = glm::vec3(1, 1, 1);
     forward = glm::vec3(0,0,1);
     right = glm::vec3(-1,0,0);
     moved = false;
}

Transform::~Transform(){
    std::cout << "deleted transform" << '\n';
}

void Transform::translate(float x, float y, float z){
    position += glm::vec3(x, y, z);
    moved = true;
}

void Transform::rotate(float x, float y, float z){
    rotation *= glm::quat(glm::vec3(x, y, z));
    rotation = glm::normalize(rotation);
    calcDirectionVectors();
}

void Transform::scale(float x, float y, float z){
    size *= glm::vec3(x, y, z);
}

void Transform::setPosition(float x, float y, float z){
    position = glm::vec3(x, y, z);
    moved = true;
    std::cout << "Set Pos Position: " << &position << std::endl;
}

void Transform::setRotation(float x, float y, float z){
    rotation = glm::quat(glm::vec3(x, y, z));
    calcDirectionVectors();
}

void Transform::setRotation(glm::quat _rotation){
    rotation = _rotation;
    calcDirectionVectors();
}

void Transform::setScale(float x, float y, float z){
    size = glm::vec3(x, y, z);
}

glm::vec3 Transform::calcGlobalPosition() {
    return glm::vec3(calcModelMatrix()*glm::vec4(0, 0, 0, 1));
}

glm::quat Transform::calcGlobalRotation(){
    if(object->getParent()){
        return rotation * object->getParent()->transform->calcGlobalRotation();
    } else {
        return rotation;
    }
}

glm::vec3 Transform::calcGlobalScale(){
    if(object->getParent()){
        return size * object->getParent()->transform->calcGlobalScale();
    } else {
        return size;
    }
}

void Transform::calcDirectionVectors(){
    //TODO: get these values directly from rotation mat
    glm::quat rot = calcGlobalRotation();
    glm::mat4 rMat = glm::mat4_cast(rot);
    forward = glm::vec3(rMat*glm::vec4(0,0,1,0));
    right = glm::vec3(rMat*glm::vec4(-1,0,0,0));
    up = glm::vec3(rMat*glm::vec4(0, 1, 0, 0));
}

glm::mat4 Transform::calcModelMatrix(){
    glm::mat4 modelMatrix = glm::mat4(1.0);
    glm::mat4 transMat  = glm::translate(glm::mat4(1.0), position);
    glm::mat4 rotMat = glm::mat4_cast(rotation);
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0), size);
    modelMatrix = transMat * rotMat * scaleMat;

    if(object->getParent()){
        return object->getParent()->transform->calcModelMatrix() * modelMatrix;
    } else {
         return modelMatrix;
    }
}

bool Transform::hasMoved(){
    if(object->getParent() && !moved){
        return object->getParent()->transform->hasMoved();
    } else {
        bool m = moved;
        moved = false;
        return m;
    }
}
