#include "Game.hpp"

#include <iostream>

#include "ShaderProgram.hpp"
#include "VAO.hpp"

class MyGame : public Engine::Game {
public:
    MyGame(){};
    virtual void start();
    virtual void update();
    virtual void finish();
private:
    Engine::Entity& sprite = entityManager.addEntity();

};
