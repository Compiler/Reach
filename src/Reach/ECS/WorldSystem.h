#pragma once
#include <Reach/Reach.h>
#include <Reach/ECS/System.h>
#include <Reach/ECS/Components.h>
#include <entt/entt.hpp>
#include <Reach/Tools/Input/InputManager.h>
#include <Reach/Tools/Utils/MathHelpers.h>

namespace reach{


    class WorldSystem : public reach::System{
        public:
            virtual void update(entt::basic_registry<entt::entity>* registry) override;
    };


}


