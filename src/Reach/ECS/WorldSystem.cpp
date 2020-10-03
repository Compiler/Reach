#include "WorldSystem.h"

//TODO: no loops for this
void reach::WorldSystem::update(entt::basic_registry<entt::entity>* registry){
        auto group = registry->view<WorldComponent>();
        auto collidables = registry->view<TransformComponent, CollidableComponent>();
        for(auto entity: group) {
            auto& world = group.get<WorldComponent>(entity);
            auto camera = world.worldCamera;
            camera->update();
            float rLimit = world.rowLimit;
            float cLimit = world.columnLimit;
            float ratioX = (camera->getRight() - camera->getLeft()) / rLimit;
            float ratioY = (camera->getTop() - camera->getBottom()) / cLimit;
            REACH_WARN("Ratios: " << ratioX << ", " << ratioY);
            float segmentChunkStartX, segmentChunkStartY;
            for(int r = 0; r < world.rowLimit; r++){
                for(int c = 0; c < world.columnLimit; c++){
                    int segmentIndex = (c*world.rowLimit) + r;
                    auto& segment = world.spacialEntities[segmentIndex];
                    segment.entities.clear();//FIX THIS
                    segmentChunkStartX = camera->getLeft() + (ratioX * ((float)r));
                    segmentChunkStartY = camera->getBottom() + (ratioY * ((float)c));
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
                if(segment.size() >= 2){
                    REACH_LOG("2 is same sector");
                    for(int k = 1; k < segment.size(); k++){
                        auto bodyA = segment[k-1];
                        auto bodyB = segment[k];
                        auto collidables = registry->view<TransformComponent, CollidableComponent>();
                        auto& bodyATrans = collidables.get<TransformComponent>(bodyA); 
                        auto& bodyBTrans = collidables.get<TransformComponent>(bodyB); 
                        glm::vec2 bodyACenter = bodyATrans.position + (bodyATrans.scale / 2.0f);
                        glm::vec2 bodyBCenter = bodyBTrans.position + (bodyBTrans.scale / 2.0f);
                        if(bodyATrans.position.x >= bodyBTrans.position.x && bodyATrans.position.x <= bodyBTrans.position.x + bodyBTrans.scale.x){
                            REACH_WARN("Collision");
                        }
                    }

                }
            }
        }

        

}