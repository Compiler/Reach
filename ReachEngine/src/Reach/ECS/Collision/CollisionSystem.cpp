#include "CollisionSystem.h"

void reach::CollisionSystem::update(entt::basic_registry<entt::entity>* registry){
    auto worldGroup = registry->view<WorldComponent>();
    auto collidables = registry->view<TransformComponent, CollidableComponent>();
    for(auto worldEntity: worldGroup) {
        auto& world = worldGroup.get<WorldComponent>(worldEntity);

        

    }
}