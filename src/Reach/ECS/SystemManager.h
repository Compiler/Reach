#pragma once
#include <Reach/ECS/System.h>
#include <vector>

namespace reach{

    class SystemManager{

        private:
            std::vector<reach::System*> _systems;

        public:
            
            template<typename T>
            T* emplaceSystem(){
                T* t = new T();
                _systems.push_back(t);
                return t;
            }
            void addSystem(reach::System* system);
            void update(entt::basic_registry<entt::entity>* registry);


    };



}