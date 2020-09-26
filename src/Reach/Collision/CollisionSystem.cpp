#include "CollisionSystem.h"


void reach::CollisionSystem::update(entt::basic_registry<entt::entity>* registry){
    auto group = registry->view<TransformComponent, CollidableComponent>();
    for(auto en: group){
        auto&&[transform, physics] = group.get<TransformComponent, PhysicsComponent>(en);
        getProjectedPosition(registry, transform.position);
    }   


}

void reach::CollisionSystem::getProjectedPosition(entt::basic_registry<entt::entity>* registry, glm::vec2& placeToGo){
    auto group = registry->view<TransformComponent, CollidableComponent>();
    for(auto entity: group) {
        auto&&[transform, physics] = group.get<TransformComponent, PhysicsComponent>(entity);
        if(reach::InputManager::isKeyPressed(KeyCodes::KEY_8)){
            physics.velocity += glm::vec2(0, -0.0000000981f);
            REACH_LOG("POG!");
        }
        //transform.position += physics.velocity;
    }


}