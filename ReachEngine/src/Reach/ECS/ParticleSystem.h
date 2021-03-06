#pragma once
#include <GLFW/glfw3.h>
#include <Reach/ECS/System.h>
#include <Reach/ECS/Components.h>
#include <Reach/Tools/Utils/Random.h>
#include <Reach/Tools/Utils/MathHelpers.h>
namespace reach{


    class ParticleSystem: public System{


        public:

            virtual void update(entt::basic_registry<entt::entity>* registry) override;
            virtual ~ParticleSystem(){};


    };


}