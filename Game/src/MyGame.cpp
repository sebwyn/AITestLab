#include "MyGame.hpp"

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "OBJLoader.hpp"

#include "Renderables/SimpleRenderable.hpp"
#include "Components/FirstPersonController.hpp"

using namespace Engine;

void MyGame::start(){

    cubeVAO = new VAO();
    OBJLoader::loadOBJ(cubeVAO, "../Assets/cube.obj");

    GameObject* obstacle = new GameObject("cube1", true);
    obstacle->attachComponent(new SimpleRenderable(cubeVAO));
    root->addChild(obstacle);

    //camera->attachComponent(new FirstPersonController());
    Transform* cameraTrans = (Transform*)camera->getComponent("transform");
    cameraTrans->setPosition(10,10,10);
    ((Camera*)camera->getComponent("camera"))->lookAt(obstacle);
}

void MyGame::update(){

}
