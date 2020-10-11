#include "CollisionSystem.h"


void reach::CollisionSystem::update(entt::basic_registry<entt::entity>* registry){
    auto group = registry->view<TransformComponent, CollidableComponent>();
    for(auto en: group){
        auto&&[transform, physics] = group.get<TransformComponent, PhysicsComponent>(en);
        
    }   


}
