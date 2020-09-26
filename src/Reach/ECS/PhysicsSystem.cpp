#include "PhysicsSystem.h"

void reach::PhysicsSystem::update(entt::basic_registry<entt::entity>* registry){
    //for(auto &&[entity, transform, physics]: registry->group<TransformComponent, PhysicsComponent>().proxy()){
        //transform.position += glm::vec2(0,-0.000981f);
    //}
    static glm::vec2 _GRAVITY_ = glm::vec2(0, -0.00000981);
    auto group = registry->view<TransformComponent, PhysicsComponent>();
    for(auto entity: group) {
        auto&&[transform, physics] = group.get<TransformComponent, PhysicsComponent>(entity);
        physics.velocity += _GRAVITY_;
        transform.position += physics.velocity;
    }
}