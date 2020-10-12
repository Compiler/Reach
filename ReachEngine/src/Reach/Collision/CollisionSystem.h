#pragma once
#include <Reach/ECS/System.h>
#include <Reach/ECS/Components.h>
#include <Reach/Tools/Input/InputManager.h>
namespace reach{


    class CollisionSystem: public System{


        public:
            static void getProjectedPosition(entt::basic_registry<entt::entity>* registry, glm::vec2& placeToGo);
            virtual void update(entt::basic_registry<entt::entity>* registry) override;
            virtual ~CollisionSystem(){};


    };


}