#include "ParticleSystemUpdater.h"



void reach::ParticleSystemUpdater::update(entt::basic_registry<entt::entity>* registry){
      auto renderables = registry->view<TransformComponent, RenderableComponent, ParticleEmitterComponent>();
        for(auto entity: renderables) {
            reach::TransformComponent &transform = renderables.get<TransformComponent>(entity);
            reach::RenderableComponent &renderable = renderables.get<RenderableComponent>(entity);
            reach::ParticleEmitterComponent &emitter = renderables.get<ParticleEmitterComponent>(entity);


            static constexpr float _MAG_ = 0.0001f;
            float directionX = 1 - ((std::rand()*10) % 2);
            float directionY = 1 - ((std::rand()*10) % 2);


            transform.position.x += directionX * emitter.velocity.x * _MAG_;
            transform.position.y += directionY * emitter.velocity.y * _MAG_;

        }

}