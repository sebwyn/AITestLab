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
        -1.0f,  1.0f, 0.0f,  // top left
         1.0f,  1.0f, 0.0f,  // top right
         1.0f, -1.0f, 0.0f,  // bottom right
    };

    float texCoords[] = {
        1.0f, 0.0f,         // bottom right
        0.0f, 0.0f,         // bottom left
        0.0f, 1.0f,         // top left
        0.0f, 1.0f,         // top left
        1.0f, 1.0f,         // top right
        1.0f, 0.0f          // bottom right
    };

    VAO* vao = new VAO();
    vao->addFloatBuffer(0,positions,6,3);
    vao->addFloatBuffer(1,texCoords,6,2);

    Texture* tex = new Texture("../Assets/terrain.png");

    GameObject* sprite = new GameObject("cube1", true);
    sprite->attachComponent(new TileChunkRenderable(vao));
    TileChunkRenderable* spriteRender = ((TileChunkRenderable*)sprite->getComponent("renderable"));
    spriteRender->addTexture(tex);
    spriteRender->setSheetSize(21,23);
    spriteRender->setTile(6,6);

    root->addChild(sprite);

    //camera->attachComponent(new FirstPersonController());
    Transform* cameraTrans = (Transform*)camera->getComponent("transform");
    cameraTrans->setPosition(0,0,1.5);
    ((Camera*)camera->getComponent("camera"))->lookAt(sprite);
}

void MyGame::update(){

}
