#include "MyGame.hpp"

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "OBJLoader.hpp"

#include "Components/Renderable.hpp"
#include "Components/FirstPersonController.hpp" 

using namespace Engine;

void MyGame::start(){
    simple = new ShaderProgram("../../Engine/Shaders/simple.vs", "../../Engine/Shaders/simple.fs");
    cubeVAO = new VAO();
    OBJLoader::loadOBJ(cubeVAO, "../Assets/cube.obj");

    GameObject* cube = new GameObject("cube", true);
    cube->attachComponent(new Renderable(cubeVAO, simple));
    root->addChild(cube);

    camera->attachComponent(new FirstPersonController());
}

void MyGame::update(){
    
}
