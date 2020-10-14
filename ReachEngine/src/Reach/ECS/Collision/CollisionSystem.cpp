#include "CollisionSystem.h"

void reach::CollisionSystem::update(entt::basic_registry<entt::entity>* registry){
    auto worldGroup = registry->view<WorldComponent>();
    auto collidables = registry->view<TransformComponent, CollidableComponent>();
    for(auto worldEntity: worldGroup) {
        auto& world = worldGroup.get<WorldComponent>(worldEntity);

        //begin doing things with segments
            for(int i = 0; i < world.spacialEntities.size(); i++){
                auto& segment = world.spacialEntities[i].entities;
                if(segment.size() >= 2){
                    //REACH_LOG("2 is same sector");
                    for(int k = 1; k < segment.size(); k++){
                        auto&&[bodyATransform, bodyACollidable] = collidables.get<TransformComponent, CollidableComponent>(segment[0]);
                        auto&&[bodyBTransform, bodyBCollidable] = collidables.get<TransformComponent, CollidableComponent>(segment[1]);
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
                                }else{                                                          //a horizontal collision
                                    leftMostEntityCollidable-> rightAxis = false;
                                    rightMostEntityCollidable->leftAxis = false;
                                }
                            }
                        }
                    }

                }
            }
    }
}