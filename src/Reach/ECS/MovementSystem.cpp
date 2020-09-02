#include "MovementSystem.h"


void reach::MovementSystem::update(entt::basic_registry<entt::entity>* registry, float deltaTime){
    auto renderables = registry->view<TransformComponent, MovementComponent>();
        for(auto entity: renderables) {
            reach::TransformComponent &transform = renderables.get<TransformComponent>(entity);
            reach::MovementComponent &movement = renderables.get<MovementComponent>(entity);
            
            assert(movement.keys.size() == movement.velocities.size());

            for(int key = 0; key < movement.keys.size(); key++)
                if(InputManager::isKeyPressed(movement.keys[key]))
                    transform.position += movement.velocities[key];
            
            
        }

}