#pragma once
#include <Reach/ECS/System.h>
#include <Reach/ECS/Components.h>
namespace reach{


    class CollisionSystem: public System{


        public:

            virtual void update(entt::basic_registry<entt::entity>* registry) override;
            virtual ~CollisionSystem(){};


    };


}