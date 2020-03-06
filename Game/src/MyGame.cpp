#include "MyGame.hpp"

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "OBJLoader.hpp"

#include "Collider.hpp"
#include "Renderable.hpp"
#include "FirstPersonController.hpp"

using namespace Engine;

void MyGame::start(){

    simple = new ShaderProgram("../../Engine/Shaders/simple.vs", "../../Engine/Shaders/simple.fs");

    cubeVAO = new VAO();
    OBJLoader::loadOBJ(cubeVAO, "../Assets/cube.obj");

    GameObject* obstacle = new GameObject("cube1", true);
    obstacle->attachComponent(new Renderable(cubeVAO, simple));
    obstacle->attachComponent(new Collider(1, 1, 1));
    root->addChild(obstacle);

    camera->attachComponent(new FirstPersonController());
}

void MyGame::update(){

}
