#include "Game.hpp"

#include <iostream>

#include "Components/Animator.hpp"
#include "ShaderProgram.hpp"
#include "VAO.hpp"

class MyGame : public Engine::Game {
public:
    MyGame(){};
    virtual void start();
    virtual void update();
private:
    Engine::GameObject* sprite;

};
