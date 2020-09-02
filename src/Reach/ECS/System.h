#pragma once
#include <entt/entity/registry.hpp>

namespace reach{


    class System{
        public:
            virtual void update(entt::basic_registry<entt::entity>* registry, float deltaTime = 0.0f) = 0;

    };

}