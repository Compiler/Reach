#include "MovementSystem.h"


void reach::MovementSystem::update(entt::basic_registry<entt::entity>* registry){
        auto group = registry->view<MovementComponent, PhysicsComponent>();
        for(auto entity: group) {
            auto&&[movement, physics] = group.get<MovementComponent, PhysicsComponent>(entity);
            assert(movement.keys.size() == movement.velocities.size());
            for(int key = 0; key < movement.keys.size(); key++)
                if(InputManager::isKeyPressed(movement.keys[key]))
                    physics.velocity += movement.velocities[key];
            
            
        }

        auto group2 = registry->view<MovementComponent, TransformComponent, CollidableComponent>(entt::exclude<PhysicsComponent>);
        for(auto entity: group2) {
            auto&&[movement, transform, collidable] = group2.get<MovementComponent, TransformComponent, CollidableComponent>(entity);
            assert(movement.keys.size() == movement.velocities.size());
            for(int key = 0; key < movement.keys.size(); key++)
                if(InputManager::isKeyPressed(movement.keys[key])){
                    glm::vec2 velocity = movement.velocities[key];
                    if(velocity.x < 0 && !collidable.leftAxis) velocity.x = 0;
                    if(velocity.x > 0 && !collidable.rightAxis) velocity.x = 0;
                    transform.position += velocity;
                }
            
            
        }

}