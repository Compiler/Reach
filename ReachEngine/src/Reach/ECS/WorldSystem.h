#pragma once
#include <Reach/Reach.h>
#include <Reach/ECS/System.h>
#include <Reach/ECS/Components.h>
#include <entt/entt.hpp>
#include <Reach/Tools/Input/InputManager.h>
#include <Reach/Tools/Utils/MathHelpers.h>

namespace reach{

    /**
     * WorldSystem will take all the entities in the world and store them into spatially partitioned segments. These segments
     * will contain entities that are near eachother and thus ready for collision. This will be passed to the CollisionSystem to handle
     * in a future call.
     */
    class WorldSystem : public reach::System{
        public:
            virtual void update(entt::basic_registry<entt::entity>* registry) override;
    };


}


