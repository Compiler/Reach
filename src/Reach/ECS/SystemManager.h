#pragma once
#include <Reach/ECS/System.h>
#include <vector>

namespace reach{

    class SystemManager{

        private:
            std::vector<reach::System*> _systems;

        public:
            
            void addSystem(reach::System* system);
            void update(entt::basic_registry<entt::entity>* registry);


    };



}