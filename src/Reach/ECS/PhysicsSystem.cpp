#include "PhysicsSystem.h"

void reach::PhysicsSystem::update(entt::basic_registry<entt::entity>* registry){
    //for(auto &&[entity, transform, physics]: registry->group<TransformComponent, PhysicsComponent>().proxy()){
        //transform.position += glm::vec2(0,-0.000981f);
    //}
    auto group = registry->view<TransformComponent, PhysicsComponent>();
    for(auto entity: group) {
        auto&&[transform, physics] = group.get<TransformComponent, PhysicsComponent>(entity);
        physics.velocity += glm::vec2(0, -0.0000000981f);
        transform.position += physics.velocity;
    }
}