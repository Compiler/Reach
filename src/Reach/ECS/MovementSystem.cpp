#include "MovementSystem.h"


void reach::MovementSystem::update(entt::basic_registry<entt::entity>* registry){
        auto renderables = registry->view<MovementComponent, PhysicsComponent>();
        for(auto entity: renderables) {
            reach::PhysicsComponent &physics = renderables.get<PhysicsComponent>(entity);
            reach::MovementComponent &movement = renderables.get<MovementComponent>(entity);
            
            assert(movement.keys.size() == movement.velocities.size());

            for(int key = 0; key < movement.keys.size(); key++)
                if(InputManager::isKeyPressed(movement.keys[key]))
                    physics.velocity += movement.velocities[key];
            
            
        }

}