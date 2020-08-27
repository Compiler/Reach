#pragma once
#include <Reach/ECS/System.h>


namespace reach{


    class ParticleSystemUpdater: public System{


        public:

            virtual void update(entt::basic_registry<entt::entity>* registry) override;


    };


}