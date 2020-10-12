#pragma once
#include <Reach/Reach.h>
#include <entt/entity/registry.hpp>

namespace reach{


    class System{
        public:
            virtual void update(entt::basic_registry<entt::entity>* registry) = 0;

    };

}