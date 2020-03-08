#include "Game.hpp"

#include "Components/Animator.hpp"
#include "ShaderProgram.hpp"
#include "VAO.hpp"

class MyGame : public Engine::Game {
public:
    MyGame(){};
    virtual void start();
    virtual void update();
private:

    Engine::VAO *cubeVAO;

    //this is inherited from Engine::Game
    //Engine::GameObject* root;
};
