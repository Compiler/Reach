#include "CollisionSystem.h"


void reach::CollisionSystem::update(entt::basic_registry<entt::entity>* registry){
    auto group = registry->view<TransformComponent, CollidableComponent>();
    for(auto en: group){
        auto&&[transform, collidable] = group.get<TransformComponent, CollidableComponent>(en);
        
    }   


}
