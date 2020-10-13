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
            /*for(int r = 0; r < world.rowLimit; r++){
                for(int c = 0; c < world.columnLimit; c++){
                    int segmentIndex = (c*world.rowLimit) + r;
                    auto& segment = world.spacialEntities[segmentIndex];
                    segment.entities.clear();//FIX THIS
                    segmentChunkStartX = camera->getLeft() + (segmentSizeX * ((float)r));
                    segmentChunkStartY = camera->getBottom() + (segmentSizeY * ((float)c));
                    //REACH_DEBUG("SegmentChunkStart Position: " << segmentChunkStartX << ", " << segmentChunkStartY);
            

                    for(auto eCollidable: collidables) {
                        auto&&[transform, collidable] = collidables.get<TransformComponent, CollidableComponent>(eCollidable);
                        if(transform.position.x <= segmentChunkStartX + segmentSizeX && transform.position.x >= segmentChunkStartX) 
                            if(transform.position.y <= segmentChunkStartY + segmentSizeY && transform.position.y >= segmentChunkStartY){
                                segment.entities.push_back(eCollidable);
                                //REACH_LOG("Added entity x,y = " << transform.position.x << ", " << transform.position.y <<  "to c,r = " << c << ", " << r);
                            }
                        
                    }

                }

            }*/

            //begin doing things with segments
            for(int i = 0; i < world.spacialEntities.size(); i++){
                auto& segment = world.spacialEntities[i].entities;
                if(segment.size() >= 2){
                    REACH_LOG("2 is same sector");
                    for(int k = 0; k < segment.size(); k++){
                        
                    }

                }
            }
        }

        

}