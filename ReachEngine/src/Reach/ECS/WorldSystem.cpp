#include "WorldSystem.h"

//TODO: no loops for this
void reach::WorldSystem::update(entt::basic_registry<entt::entity>* registry){
        auto group = registry->view<WorldComponent>();
        auto collidables = registry->view<TransformComponent, CollidableComponent>();
        for(auto entity: group) {
            auto& world = group.get<WorldComponent>(entity);
            auto camera = world.worldCamera;
            camera->update();
            float rLimit = world.getRowLimit();
            float cLimit = world.getColumnLimit();
            float segmentSizeX = (camera->getRight() - camera->getLeft()) / rLimit;
            float segmentSizeY = (camera->getTop() - camera->getBottom()) / cLimit;
            //Debug code
            if(InputManager::isKeyPressed(KeyCodes::KEY_SPACE))
                REACH_WARN("SegmentDimensions: (" << segmentSizeX << ", " << segmentSizeY << ")");
            float segmentChunkStartX, segmentChunkStartY;
            world.clearSegments();
            //Figure out why the segments arent starting at the correct ratios.. instead its off by a uniform amountasw
            for(auto eCollidable: collidables) {
                auto&&[transform, collidable] = collidables.get<TransformComponent, CollidableComponent>(eCollidable);
                collidable.reset();
                if( transform.position.x + transform.scale.x <= camera->getLeft() || transform.position.x >= camera->getRight() ||
                    transform.position.y + transform.scale.y <= camera->getBottom() || transform.position.y >= camera->getTop() ){
                    //REACH_ERROR("Skipped");
                    continue;
                }

                
                int rowIndex = abs(roundInterval(transform.position.x, segmentSizeX) / segmentSizeX);
                int columnIndex = abs(roundInterval(transform.position.y, segmentSizeY) / segmentSizeY);
                int segmentIndex = (columnIndex*world.getRowLimit()) + rowIndex;
                //world.spacialEntities[segmentIndex].entities.push_back(eCollidable);

                int widthIndex = abs(roundInterval(transform.position.x + transform.scale.x, segmentSizeX) / segmentSizeX);
                int heightIndex = abs(roundInterval(transform.position.y + transform.scale.y, segmentSizeY) / segmentSizeY);

                //REACH_LOG("Added " << rowIndex<< ", " << columnIndex );

                for(int k = 0; k <= heightIndex - columnIndex; k++){
                    for(int i = 0; i <= widthIndex - rowIndex; i++){
                        //REACH_LOG("Added " << rowIndex + i << ", " << columnIndex + k);
                        int index = ((columnIndex + k)*world.getRowLimit()) + rowIndex + i;
                        if(index > world.spacialEntities.size()) continue;
                        world.spacialEntities[index].entities.push_back(eCollidable);
                    }

                }
                

                //Debug code
                if(InputManager::isKeyPressed(KeyCodes::KEY_SPACE)){
                    if(transform.position.x == 300 && transform.position.y == 500){
                        REACH_ERROR("Position: (" << transform.position.x << ", " << transform.position.y << ")");
                        REACH_ERROR("RoundIntervalPosition: (" << roundInterval(transform.position.x, segmentSizeX) / segmentSizeX << ", " << roundInterval(transform.position.y, segmentSizeY) / segmentSizeY << ")");
                    }
                    else{
                        REACH_DEBUG("Position: (" << transform.position.x << ", " << transform.position.y << ")");
                        REACH_DEBUG("RoundIntervalPosition: (" << roundInterval(transform.position.x, segmentSizeX) / segmentSizeX << ", " << roundInterval(transform.position.y, segmentSizeY) / segmentSizeY << ")");
                    }
                }
            }
            for(int i = 0; i < world.spacialEntities.size(); i++){
                auto& segment = world.spacialEntities[i].entities;
                if(segment.size() >= 2){
                    //REACH_LOG("2 is same sector");
                    for(int k = 1; k < segment.size(); k++){
                        static constexpr glm::vec2 AXIS = glm::vec2(1, -1);
                        auto&&[bodyATransform, bodyACollidable] = collidables.get<TransformComponent, CollidableComponent>(segment[k-1]);
                        auto&&[bodyBTransform, bodyBCollidable] = collidables.get<TransformComponent, CollidableComponent>(segment[k]);
                        assert(&bodyATransform != &bodyBTransform);
                        bool allAxisCollide = true;
                        int numAxisColliding = 0;
                        for(int bodyCount = 0; bodyCount < 2; bodyCount ++){
                            glm::vec2 bodyAPoints[4], bodyBPoints[4];
                            if(bodyCount == 0){
                                bodyAPoints[0] = glm::vec2(bodyATransform.position.x, bodyATransform.position.y);
                                bodyAPoints[1] = glm::vec2(bodyATransform.position.x, bodyATransform.position.y + bodyATransform.scale.y);
                                bodyAPoints[2] = glm::vec2(bodyATransform.position.x + bodyATransform.scale.x, bodyATransform.position.y + bodyATransform.scale.y);
                                bodyAPoints[3] = glm::vec2(bodyATransform.position.x + bodyATransform.scale.x, bodyATransform.position.y);
                                bodyBPoints[0] = glm::vec2(bodyBTransform.position.x, bodyBTransform.position.y);
                                bodyBPoints[1] = glm::vec2(bodyBTransform.position.x, bodyBTransform.position.y + bodyBTransform.scale.y);
                                bodyBPoints[2] = glm::vec2(bodyBTransform.position.x + bodyBTransform.scale.x, bodyBTransform.position.y + bodyBTransform.scale.y);
                                bodyBPoints[3] = glm::vec2(bodyBTransform.position.x + bodyBTransform.scale.x, bodyBTransform.position.y);
                            }else{
                                bodyBPoints[0] = glm::vec2(bodyATransform.position.x, bodyATransform.position.y);
                                bodyBPoints[1] = glm::vec2(bodyATransform.position.x, bodyATransform.position.y + bodyATransform.scale.y);
                                bodyBPoints[2] = glm::vec2(bodyATransform.position.x + bodyATransform.scale.x, bodyATransform.position.y + bodyATransform.scale.y);
                                bodyBPoints[3] = glm::vec2(bodyATransform.position.x + bodyATransform.scale.x, bodyATransform.position.y);
                                bodyAPoints[0] = glm::vec2(bodyBTransform.position.x, bodyBTransform.position.y);
                                bodyAPoints[1] = glm::vec2(bodyBTransform.position.x, bodyBTransform.position.y + bodyBTransform.scale.y);
                                bodyAPoints[2] = glm::vec2(bodyBTransform.position.x + bodyBTransform.scale.x, bodyBTransform.position.y + bodyBTransform.scale.y);
                                bodyAPoints[3] = glm::vec2(bodyBTransform.position.x + bodyBTransform.scale.x, bodyBTransform.position.y);

                            }


                            float minProjA = std::numeric_limits<float>::max(), maxProjA = std::numeric_limits<float>::min();
                            float minProjB = std::numeric_limits<float>::max(), maxProjB = std::numeric_limits<float>::min();
                            
                            for(int axisIndex = 0; axisIndex < 4; axisIndex++){
                                int nextIndex = (axisIndex + 1) % 4;
                                glm::vec2 axis = glm::vec2(-(bodyAPoints[axisIndex].y - bodyAPoints[nextIndex].y), bodyAPoints[axisIndex].x - bodyAPoints[nextIndex].x);
                                
                                float d = sqrtf(axis.x * axis.x + axis.y * axis.y);
                                axis = glm::vec2(axis.x / d, axis.y / d);
                                for(int curProjIndex = 0; curProjIndex < 4; curProjIndex++){
                                    float curProjA = glm::dot(bodyAPoints[curProjIndex], axis);//bodyAPoints[curProjIndex].x * axis.x + bodyAPoints[curProjIndex].y * axis.y;
                                    minProjA = std::min(minProjA, curProjA);
                                    maxProjA = std::max(maxProjA, curProjA);
                                }
                                if(minProjA > maxProjA) REACH_ERROR("WRONG");
                                for(int curProjIndex = 0; curProjIndex < 4; curProjIndex++){
                                    float curProjB = bodyBPoints[curProjIndex].x * axis.x + bodyBPoints[curProjIndex].y * axis.y;
                                    minProjB = std::min(minProjB, curProjB);
                                    maxProjB = std::max(maxProjB, curProjB);
                                }
                                if(minProjB > maxProjB) REACH_ERROR("WRONG");
                                if(maxProjB < minProjA || maxProjA < minProjB){
                                    allAxisCollide = false;
                                    //REACH_ERROR("!NO COLLISION:\nA\t'" << minProjA << "' , '" << maxProjA << "'\nB\t'" << minProjB << "' , '" << maxProjB << "'");
                                    //REACH_ERROR("bool:\t'" << maxProjB << " < " << minProjA << " || " << maxProjA << " < " << minProjB);
                                    //REACH_WARN("num: " << numAxisColliding);
                                    break;
                                }else{
                                    //REACH_DEBUG("COLLISION:\nA\t'" << minProjA << "' , '" << maxProjA << "'\nB\t'" << minProjB << "' , '" << maxProjB << "'");
                                    //REACH_DEBUG("bool:\t'" << maxProjB << " >= " << minProjA << " && " << maxProjA << " >= " << minProjB);

                                }

                                numAxisColliding ++;
                            }
                        }
                        if(!allAxisCollide) REACH_ERROR("gap touched: " << numAxisColliding);
                        else REACH_LOG("TOUCHED " << numAxisColliding);
                        //REACH_ERROR("chose : A = " << minProjA << ", " << maxProjA << ", B = " << minProjB << ", " << maxProjB);
                        

                        
                    }

                }
            }

        }

        

}