#include "WorldSystem.h"

//TODO: no loops for this
void reach::WorldSystem::update(entt::basic_registry<entt::entity>* registry){
        int count = 0;
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
                if( transform.position.x <= camera->getLeft() || transform.position.x >= camera->getRight() ||
                    transform.position.y <= camera->getBottom() || transform.position.y >= camera->getTop() ){
                    REACH_ERROR("Skipped");
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
                        auto&&[bodyATransform, bodyACollidable] = collidables.get<TransformComponent, CollidableComponent>(segment[k-1]);
                        auto&&[bodyBTransform, bodyBCollidable] = collidables.get<TransformComponent, CollidableComponent>(segment[k]);
                        assert(&bodyATransform != &bodyBTransform);
                        TransformComponent* leftMostEntityTransform, *rightMostEntityTransform, *topMostEntityTransform, *bottomMostEntityTransform;
                        CollidableComponent* leftMostEntityCollidable, *rightMostEntityCollidable, *topMostEntityCollidable, *bottomMostEntityCollidable;
                        if(bodyATransform.position.x <= bodyBTransform.position.x){
                            leftMostEntityTransform = &bodyATransform;
                            leftMostEntityCollidable = &bodyACollidable;
                            rightMostEntityTransform = &bodyBTransform;
                            rightMostEntityCollidable = &bodyBCollidable;
                        }else{
                            leftMostEntityTransform = &bodyBTransform;
                            leftMostEntityCollidable = &bodyBCollidable;
                            rightMostEntityTransform = &bodyATransform;
                            rightMostEntityCollidable = &bodyACollidable;
                        }
                        if(bodyATransform.position.y > bodyBTransform.position.y){
                            topMostEntityTransform = &bodyATransform;
                            topMostEntityCollidable = &bodyACollidable;
                            bottomMostEntityTransform = &bodyBTransform;
                            bottomMostEntityCollidable = &bodyBCollidable;
                        }else{
                            topMostEntityTransform = &bodyBTransform;
                            topMostEntityCollidable = &bodyBCollidable;
                            bottomMostEntityTransform = &bodyATransform;
                            bottomMostEntityCollidable = &bodyACollidable;

                        }
                        glm::vec2& leftMostPosition = leftMostEntityTransform->position;
                        glm::vec2& rightMostPosition = rightMostEntityTransform->position;
                        glm::vec2& topMostPosition = topMostEntityTransform->position;
                        glm::vec2& bottomMostPosition = bottomMostEntityTransform->position;
                        glm::vec2& leftMostScale = leftMostEntityTransform->scale;
                        glm::vec2& rightMostScale = rightMostEntityTransform->scale;
                        glm::vec2& topMostScale = topMostEntityTransform->scale;
                        glm::vec2& bottomMostScale = bottomMostEntityTransform->scale;
                        
                        static constexpr int _SEP_ = 0;
                        if(topMostPosition.y <= bottomMostPosition.y + bottomMostScale.y && topMostPosition.y >= bottomMostPosition.y){ //if vertical collision
                            if(rightMostPosition.x <= leftMostPosition.x + leftMostScale.x && rightMostPosition.x >= leftMostPosition.x){//if horizontal axis collision
                                if(leftMostPosition.x + leftMostScale.x > rightMostPosition.x){ //a vertical only collision
                                    topMostEntityCollidable->bottomAxis = false;
                                    bottomMostEntityCollidable->topAxis = false;
                                } //a horizontal collision
                                    rightMostEntityCollidable->leftAxis = false;
                                    leftMostEntityCollidable-> rightAxis = false;
                                                                                         
                            }
                        }
                    }

                }
            }

        }

        

}