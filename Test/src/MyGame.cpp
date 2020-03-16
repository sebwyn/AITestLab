#include "MyGame.hpp"

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "OBJLoader.hpp"

#include "Renderables/TileChunkRenderable.hpp"
#include "Components/FirstPersonController.hpp"

#include "Texture.hpp"

using namespace Engine;

void MyGame::start(){

    float positions[] = {
        // positions
         1.0f, -1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f,  // bottom left
        -1.0f,  1.0f, 0.0f,  // top left
         1.0f,  1.0f, 0.0f,  // top right
    };

    float texCoords[] = {
        1.0f, 0.0f,         // bottom right
        0.0f, 0.0f,         // bottom left
        0.0f, 1.0f,         // top left
        1.0f, 1.0f,         // top right
    };

    GLshort indices[] = {
        0,1,2,2,3,0
    };

    VAO* vao = new VAO();
    vao->addFloatBuffer(0,positions,6,3);
    vao->addFloatBuffer(1,texCoords,6,2);
    vao->addElementBuffer(indices,6);

    Texture* tex = new Texture("Assets/terrain.png");

    sprite = new GameObject("cube1", true);
    sprite->attachComponent(new TileChunkRenderable(vao));
    TileChunkRenderable* spriteRender = ((TileChunkRenderable*)sprite->getComponent("renderable"));
    spriteRender->addTexture(tex);
    spriteRender->setSheetSize(21,23);
    spriteRender->setTile(6,6);
    sprite->transform->setPosition(0,0,0);

    root->addChild(sprite);
    std::cout << "hi" << std::endl;

    camera->attachComponent(new FirstPersonController());
    camera->transform->setPosition(0,0,1.5);
    //((Camera*)camera->getComponent("camera"))->lookAt(0,0,0);
    //((Camera*)camera->getComponent("camera"))->ortho();
}

void MyGame::update(){
    //sprite->transform->translate(0.1,0.1,0);
}
