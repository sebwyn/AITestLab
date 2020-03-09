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
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        0.0f,  0.5f, 0.0f   // top center
    };

    float colors[] = {
        0.0f, 1.0f, 0.0f,   // bottom right
        0.0f, 0.0f, 1.0f,   // bottom left
        1.0f, 0.0f, 0.0f,   // top center
    };

    float texCoords[] = {
        1.0f, 0.0f,         // bottom right
        0.0f, 0.0f,         // bottom left
        0.5f, 1.0f          // top center
    };

    VAO* vao = new VAO();
    vao->addFloatBuffer(0,positions,4,3);
    vao->addFloatBuffer(1,colors,4,3);
    vao->addFloatBuffer(2,texCoords,4,2);

    Texture tex = Texture("../Assets/test.png");

    GameObject* sprite = new GameObject("cube1", true);
    sprite->attachComponent(new TileChunkRenderable(vao));
    ((TileChunkRenderable*)sprite->getComponent("renderable"))
                                 ->addTexture(&tex);
    root->addChild(sprite);

    camera->attachComponent(new FirstPersonController());
    //Transform* cameraTrans = (Transform*)camera->getComponent("transform");
    //cameraTrans->setPosition(10,10,10);
    //((Camera*)camera->getComponent("camera"))->lookAt(sprite);
}

void MyGame::update(){

}
