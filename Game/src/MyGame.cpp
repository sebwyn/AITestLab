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

    float colors[] = {
        0.0f, 1.0f, 0.0f,   // bottom right
        0.0f, 0.0f, 1.0f,   // bottom left
        1.0f, 0.0f, 0.0f,   // top left
        1.0f, 0.0f, 0.0f,   // top left
        1.0f, 1.0f, 1.0f,   // top right
        0.0f, 1.0f, 0.0f    // bottom right
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
    vao->addFloatBuffer(1,colors,6,3);
    vao->addFloatBuffer(2,texCoords,6,2);

    Texture* tex = new Texture("../Assets/terrain.png");

    GameObject* sprite = new GameObject("cube1", true);
    sprite->attachComponent(new TileChunkRenderable(vao));
    ((TileChunkRenderable*)sprite->getComponent("renderable"))
                                 ->addTexture(tex);
    root->addChild(sprite);

    camera->attachComponent(new FirstPersonController());
    //Transform* cameraTrans = (Transform*)camera->getComponent("transform");
    //cameraTrans->setPosition(10,10,10);
    //((Camera*)camera->getComponent("camera"))->lookAt(sprite);
}

void MyGame::update(){

}
