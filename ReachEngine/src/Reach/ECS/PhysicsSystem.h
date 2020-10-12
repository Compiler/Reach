#pragma once
#include <Reach/Reach.h>
#include <Reach/ECS/System.h>
#include <Reach/ECS/Components.h>
#include <entt/entt.hpp>
#include <Reach/Tools/Input/InputManager.h>

namespace reach{


    class PhysicsSystem : public reach::System{
        public:
            virtual void update(entt::basic_registry<entt::entity>* registry) override;
    };


}


