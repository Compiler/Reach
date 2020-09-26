#include "WorldSystem.h"

//TODO: no loops for this
void reach::WorldSystem::update(entt::basic_registry<entt::entity>* registry){
        auto group = registry->view<WorldComponent>();
        auto collidables = registry->view<TransformComponent, CollidableComponent>();
        for(auto entity: group) {
            auto& world = group.get<WorldComponent>(entity);
            for(int r = 0; r < world.rowLimit; r++){
                for(int c = 0; c < world.columnLimit; c++){
                    int segmentIndex = (c*world.rowLimit) + r;
                    auto& segment = world.spacialEntities[segmentIndex];
                    segment.entities.clear();//FIX THIS
                    float ratioX, ratioY,startX, startY;
                    if(r == 0) startX = 0;
                    else {
                        ratioX = (SCREEN_RIGHT - SCREEN_LEFT) / r;
                        startX = ratioX * r;
                    }

                    if(c == 0) startY = 0;
                    else {
                        ratioY = (SCREEN_RIGHT - SCREEN_LEFT) / c;
                        startY = ratioY * c;
                    }

                    for(auto eCollidable: collidables) {
                        auto&&[transform, collidable] = collidables.get<TransformComponent, CollidableComponent>(eCollidable);
                        if(transform.position.x <= startX + ratioX && transform.position.x >= startX) 
                            if(transform.position.y <= startY + ratioY && transform.position.y >= startY) segment.entities.push_back(eCollidable);
                        
                    }

                }

            }

            //begin doing things with segments
            for(int i = 0; i < world.spacialEntities.size(); i++){
                auto& segment = world.spacialEntities[i].entities;
                if(segment.size() >= 2) REACH_WARN("Two entities in same segment");
            }
        }

        

}