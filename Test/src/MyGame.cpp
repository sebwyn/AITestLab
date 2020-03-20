#include "MyGame.hpp"

#include "ShaderProgram.hpp"
#include "VAO.hpp"

#include "OBJLoader.hpp"

#include "Components/TileChunkRenderable.hpp"
#include "Components/FirstPersonController.hpp"

#include "Texture.hpp"
#include "Components/Transform.hpp"

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

    //sprite = new Entity();
    sprite.addComponent<TileChunkRenderable>(vao);
    TileChunkRenderable& spriteRender = sprite.getComponent<TileChunkRenderable>();
    spriteRender.addTexture(tex);
    spriteRender.setSheetSize(21,23);
    spriteRender.setTile(6,6);
    sprite.addComponent<Transform>();
    sprite.getComponent<Transform>().setPosition(0,0,0);

    camera.addComponent<FirstPersonController>();
    camera.getComponent<Transform>().setPosition(0,0,1.5);
    //sprite.destroy();
    //camera.getComponent<Camera>().lookAt(0,0,0);
    //((Camera*)camera->getComponent("camera"))->ortho();
}

void MyGame::update(){
    //sprite.transform->translate(0.1,0.1,0);
    if (sprite.hasComponent<TileChunkRenderable>())
    sprite.getComponent<TileChunkRenderable>()
    .setMatrices(camera.getComponent<Camera>().getProjectionMatrix(), camera.getComponent<Camera>().getViewMatrix());
}

void MyGame::finish(){
    sprite.destroy();
    entityManager.cleanUp();
    camera.destroy();
    entityManager.cleanUp();
}
