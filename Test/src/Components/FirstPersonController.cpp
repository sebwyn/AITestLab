#include "Components/FirstPersonController.hpp"

using namespace Engine;

FirstPersonController::FirstPersonController() 
    :WindowEventSubscriber() {

    WindowEventSubscriber::subscribe(WindowEventManager::events::KEYBOARD_INPUT);
    WindowEventSubscriber::subscribe(WindowEventManager::events::CURSOR_POSITION);
}

void FirstPersonController::onKey(int key, int scancode, int action, int mods) {
    vec3 fv = entity->getComponent<Transform>().getForward();
    vec3 rv = entity->getComponent<Transform>().getRight();
    if (action == GLFW_PRESS){
        switch(key){
            case GLFW_KEY_W:
                move += vec3(0, 0, 1);
                break;
            case GLFW_KEY_A:
                move -= vec3(1, 0, 0);
                break;
            case GLFW_KEY_S:
                move -= vec3(0, 0, 1);
                break;
            case GLFW_KEY_D:
                move += vec3(1, 0, 0);
                break;
            case GLFW_KEY_SPACE:
                move += vec3(0,1,0);
                break;
            case GLFW_KEY_LEFT_SHIFT:
                move -= vec3(0,1,0);
                break;
            default:
                break;
        }
    }else if (action == GLFW_RELEASE){
        switch(key){
            case GLFW_KEY_W:
                move -= vec3(0, 0, 1);
                break;
            case GLFW_KEY_A:
                move += vec3(1, 0, 0);
                break;
            case GLFW_KEY_S:
                move += vec3(0, 0, 1);
                break;
            case GLFW_KEY_D:
                move -= vec3(1, 0, 0);
                break;
            case GLFW_KEY_SPACE:
                move -= vec3(0,1,0);
                break;
            case GLFW_KEY_LEFT_SHIFT:
                move += vec3(0,1,0);
                break;
            default:
                break;
        }
    }
}

void FirstPersonController::onCursorMove(double xpos, double ypos) {
    int width = entity->getComponent<Camera>().getWidth();
    int height = entity->getComponent<Camera>().getHeight();

    rotate = vec2(0,float(width/2-xpos));
    rotate += vec2(-float(height/2-ypos),0);

}

void FirstPersonController::calcTranslation(float dt){
    if (length(move) <= 0){ translationVector = vec3(0); return;}

    vec3 forward = entity->getComponent<Transform>().getForward();
    vec3 right = entity->getComponent<Transform>().getRight();

    translationVector = (move.x*right) + (move.y*vec3(0,1,0)) + (move.z*forward);
    translationVector = normalize(translationVector) * speed * dt;
}

void FirstPersonController::calcRotation(float dt){
    rotationVector += rotate * dt * mouseSpeed;

    if (rotationVector.x > 1.5){
        rotationVector.x = 1.5;
    }else if (rotationVector.x < -1.5){
        rotationVector.x = -1.5;
    }

    rotate =  vec2(0,0);
}


void FirstPersonController::init(){
    update();
}

void FirstPersonController::update(){
    float deltaTime = float(glfwGetTime()-lastTime);
    Transform& entTf = entity->getComponent<Transform>();

    calcRotation(deltaTime);
    entTf.setRotation(rotationVector.x,rotationVector.y,0);

    calcTranslation(deltaTime);
    entTf.translate(translationVector.x,translationVector.y,translationVector.z);

    lastTime = glfwGetTime();
}
