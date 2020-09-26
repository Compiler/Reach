#include "WorldSystem.h"

//TODO: no loops for this
void reach::WorldSystem::update(entt::basic_registry<entt::entity>* registry){
        auto group = registry->view<WorldComponent>();
        auto collidables = registry->view<TransformComponent, CollidableComponent>();
        for(auto entity: group) {
            auto& world = group.get<WorldComponent>(entity);
            float rLimit = world.rowLimit;
            float cLimit = world.columnLimit;
            float ratioX = (SCREEN_RIGHT - SCREEN_LEFT) / rLimit;
            float ratioY = (SCREEN_TOP - SCREEN_BOTTOM) / cLimit;
            //REACH_WARN("Ratios: " << ratioX << ", " << ratioY);
            float segmentChunkStartX, segmentChunkStartY;
            for(int r = 0; r < world.rowLimit; r++){
                for(int c = 0; c < world.columnLimit; c++){
                    int segmentIndex = (c*world.rowLimit) + r;
                    auto& segment = world.spacialEntities[segmentIndex];
                    segment.entities.clear();//FIX THIS
                    segmentChunkStartX = SCREEN_LEFT + (ratioX * ((float)r));
                    segmentChunkStartY = SCREEN_BOTTOM + (ratioY * ((float)c));
                    //REACH_DEBUG("SegmentChunkStart Position: " << segmentChunkStartX << ", " << segmentChunkStartY);
            

                    for(auto eCollidable: collidables) {
                        auto&&[transform, collidable] = collidables.get<TransformComponent, CollidableComponent>(eCollidable);
                        if(transform.position.x <= segmentChunkStartX + ratioX && transform.position.x >= segmentChunkStartX) 
                            if(transform.position.y <= segmentChunkStartY + ratioY && transform.position.y >= segmentChunkStartY){
                                segment.entities.push_back(eCollidable);
                                //REACH_LOG("Added entity x,y = " << transform.position.x << ", " << transform.position.y <<  "to c,r = " << c << ", " << r);
                            }
                        
                    }

                }

            }

            //begin doing things with segments
            for(int i = 0; i < world.spacialEntities.size(); i++){
                auto& segment = world.spacialEntities[i].entities;
                if(segment.size() == 2) REACH_WARN("2 entities in same segment");
                if(segment.size() == 3) REACH_WARN("3 entities in same segment");
                if(segment.size() == 4) REACH_WARN("4 entities in same segment");
            }
        }

        

}