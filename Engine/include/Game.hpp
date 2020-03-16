#pragma once

#include "Window.hpp"
#include "Time.hpp"
#include "Components/Camera.hpp"
#include "ECS.hpp"

namespace Engine {

class Game {
private:
    void mainloop(){
        double previousTime = glfwGetTime();
        double pTime = previousTime;
        int frameCount = 0;

        while(!win->closed()){
            double currentTime = glfwGetTime();
            if (currentTime-previousTime > 0.016){
                frameCount++;
                if ( currentTime - pTime >= 1.0 )
                {
                    std::cout << frameCount << std::endl;
                    frameCount = 0;
                    pTime = glfwGetTime();
                }

                Time::update();
                update();


                camera.getComponent<Camera>()
                    .updateAspect(win->getWidth(), win->getHeight());
                win->clear();

                entityManager.cleanUp();
                entityManager.update();
                entityManager.draw();

                win->update();
                previousTime = currentTime;
            }
        }
    }

    void init(){
        win = new Window("Window", 1024, 768);
        win->disableCursor();

        camera.addComponent<Transform>();
        camera.addComponent<Camera>(1024,768);

        Time::start();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        //glEnable(GL_CULL_FACE);
    }

    void cleanup(){
        delete win;
    }

    Window* win;
protected:
    virtual void start(){return;};
    virtual void update(){return;};
    virtual void finish(){return;}

    Manager entityManager;
    Entity& camera = entityManager.addEntity();
public:
    Game(){}
    void run(){
        init();
        start();

        mainloop();

        finish();
        cleanup();
    }

};
}
