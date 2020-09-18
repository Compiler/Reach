#include "CollisionSystem.h"


void reach::CollisionSystem::update(entt::basic_registry<entt::entity>* registry){



}

void reach::CollisionSystem::getProjectedPosition(entt::basic_registry<entt::entity>* registry, glm::vec2& placeToGo){
    auto group = registry->view<TransformComponent, CollidableComponent>();
    for(auto entity: group) {
        auto&&[transform, physics] = group.get<TransformComponent, PhysicsComponent>(entity);
        physics.velocity += glm::vec2(0, -0.0000000981f);
        transform.position += physics.velocity;
    }


}