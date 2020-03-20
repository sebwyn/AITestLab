#pragma once

#include <memory>
#include <array>
#include <utility>
#include <algorithm>
#include <vector>
#include <bitset>
#include <iostream>

namespace Engine{
    class Component;
    class Entity;
    class Manager;
}

const int max_component_types = 32;

inline int componentTypeID(){
    static int id = 0;
    return id++;
}

template<typename T>
inline int getComponentTypeID(){
    static int typeID = componentTypeID();
    //std::cout << "TypeID : " << typeID << std::endl;
    return typeID;
}

namespace Engine {
    class Component{
    protected:
        Entity* entity;
    public:
        virtual void init() {};
        virtual void update() {};
        virtual void draw() {};

        virtual ~Component() {std::cout << "component deleted" << std::endl;};

        friend Entity;
    };

    class Entity{
        private:
            bool alive = true;

            std::vector<std::unique_ptr<Component>> components;
            std::array<Component*,max_component_types> componentLookup;
            std::bitset<max_component_types> typeList;
        public:
            virtual void update(){
                for(auto& component : components){
                    component->update();
                }
            }

            virtual void draw(){
                for (auto& component : components){
                    component->draw();
                }
            }

            void destroy() {alive = false;}

            bool destroyed() const {return !alive;}

            template<typename T>
            bool hasComponent() const {
                return typeList[getComponentTypeID<T>()];
            }

            template<typename T>
            T& getComponent() const{
                if (!hasComponent<T>()){
                    std::cout << "COULDN'T GET COMPONENT: "
                        << __PRETTY_FUNCTION__ << std::endl;
                    exit(-1);
                }
                Component* component = componentLookup[getComponentTypeID<T>()];
                return *static_cast<T*>(component);
            } 

            template<typename T, typename... args>
            T& addComponent(args&&... _args){
                T* component = new T(std::forward<args>(_args)...);
                component->entity = this;
                component->init();

                std::unique_ptr<Component> uComponent{component};
                components.emplace_back(std::move(uComponent));

                unsigned int typeID = getComponentTypeID<T>();
                typeList[typeID] = true;
                componentLookup[typeID] = component;

                return *component;
            }
    };

    class Manager{
    private:
        std::vector<std::unique_ptr<Entity>> entities;
    public:

        Entity& addEntity(){
            Entity* entity = new Entity();
            std::unique_ptr<Entity> uEntity{entity};
            entities.emplace_back(std::move(uEntity));

            return *entity;
        }

        void addEntity(Entity* entity){
            std::unique_ptr<Entity> uEntity{entity};
            entities.emplace_back(std::move(uEntity));
        }

        void cleanUp(){
            entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
                [](std::unique_ptr<Entity> &entity){
                    return entity->destroyed();
                }), std::end(entities));
        }

        void update(){
            for (auto& entity : entities){
                entity->update();
            }
        }

        void draw(){
            for (auto& entity : entities){
                entity->draw();
            }
        }
    };
}