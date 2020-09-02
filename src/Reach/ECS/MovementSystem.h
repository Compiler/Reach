#pragma once
#include <Reach/ECS/System.h>
#include <Reach/ECS/Components.h>
#include <Reach/Tools/Input/InputManager.h>
#include <entt/entity/registry.hpp>
#include <Reach/Tools/Logging/Logger.h>
namespace reach{


    class MovementSystem : public System{

        public:
            void update(entt::basic_registry<entt::entity>* registry, float deltaTime)override;

    };


}