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
            float segmentSizeX = (camera->getRight() - camera->getLeft()) / rLimit;
            float segmentSizeY = (camera->getTop() - camera->getBottom()) / cLimit;
            //Debug code
            if(InputManager::isKeyPressed(KeyCodes::KEY_SPACE))
                REACH_WARN("SegmentDimensions: (" << segmentSizeX << ", " << segmentSizeY << ")");
            float segmentChunkStartX, segmentChunkStartY;
            world.clearSegments();
            //Figure out why the segments arent starting at the correct ratios.. instead its off by a uniform amount
            for(auto eCollidable: collidables) {
                auto&&[transform, collidable] = collidables.get<TransformComponent, CollidableComponent>(eCollidable);
                if( transform.position.x <= camera->getLeft() || transform.position.x >= camera->getRight() ||
                    transform.position.y <= camera->getBottom() || transform.position.y >= camera->getTop() ){
                    REACH_ERROR("Skipped");
                    continue;
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
                int columnIndex = abs(roundInterval(transform.position.y, segmentSizeY) / segmentSizeY);
                int rowIndex = abs(roundInterval(transform.position.x, segmentSizeX) / segmentSizeX);
                int segmentIndex = (columnIndex*world.rowLimit) + rowIndex;
                //REACH_LOG("ColInd: " << columnIndex << "\tRowInd: " << rowIndex << "\tSegINd: " << segmentIndex);
                auto& segment = world.spacialEntities[segmentIndex];
                segment.entities.push_back(eCollidable);
            }

            //begin doing things with segments
            for(int i = 0; i < world.spacialEntities.size(); i++){
                auto& segment = world.spacialEntities[i].entities;
                if(segment.size() >= 2){
                    //REACH_LOG("2 is same sector");
                    for(int k = 1; k < segment.size(); k++){
                        auto&&[bodyATransform, bodyACollidable] = collidables.get<TransformComponent, CollidableComponent>(segment[0]);
                        auto&&[bodyBTransform, bodyBCollidable] = collidables.get<TransformComponent, CollidableComponent>(segment[1]);
                        TransformComponent* leftMostEntity, *rightMostEntity, *topMostEntity, *bottomMostEntity;
                        if(bodyATransform.position.x <= bodyBTransform.position.x){
                            leftMostEntity = &bodyATransform;
                            rightMostEntity = &bodyBTransform;
                        }else{
                            leftMostEntity = &bodyBTransform;
                            rightMostEntity = &bodyATransform;
                        }
                        if(bodyATransform.position.y > bodyBTransform.position.y){
                            topMostEntity = &bodyATransform;
                            bottomMostEntity = &bodyBTransform;
                        }else{
                            topMostEntity = &bodyBTransform;
                            bottomMostEntity = &bodyATransform;
                        }
                        glm::vec2& leftMostPosition = leftMostEntity->position;
                        glm::vec2& rightMostPosition = rightMostEntity->position;
                        glm::vec2& topMostPosition = topMostEntity->position;
                        glm::vec2& bottomMostPosition = bottomMostEntity->position;
                        glm::vec2& leftMostScale = leftMostEntity->scale;
                        glm::vec2& rightMostScale = rightMostEntity->scale;
                        glm::vec2& topMostScale = topMostEntity->scale;
                        glm::vec2& bottomMostScale = bottomMostEntity->scale;

                        //if horizontal axis collision
                        if(rightMostPosition.x <= leftMostPosition.x + leftMostScale.x && rightMostPosition.x >= leftMostPosition.x){
                            if(topMostPosition.y <= bottomMostPosition.y + bottomMostScale.y && topMostPosition.y >= bottomMostPosition.y){
                                REACH_DEBUG("HIT");
                            }

                        }
                    }

                }
            }
        }

        

}