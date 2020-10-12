#pragma once
#include <Reach/ECS/System.h>

namespace sandbox{


    class InventorySystem : public reach::System{


        public:
            void update(entt::basic_registry<entt::entity>* registry) override;

    };


}