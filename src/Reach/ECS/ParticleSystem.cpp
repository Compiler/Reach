#include "ParticleSystem.h"



void reach::ParticleSystem::update(entt::basic_registry<entt::entity>* registry){
        auto renderables = registry->view<TransformComponent, RenderableComponent, ParticleEmitterComponent>();
        double current = glfwGetTime();
        double elapsed = glfwGetTime() - current;
        for(auto entity: renderables) {
            current = glfwGetTime();
            reach::TransformComponent &transform = renderables.get<TransformComponent>(entity);
            reach::RenderableComponent &renderable = renderables.get<RenderableComponent>(entity);
            reach::ParticleEmitterComponent &emitter = renderables.get<ParticleEmitterComponent>(entity);
            if(emitter.offsets.size() != emitter.emissionCount) emitter.offsets.resize(emitter.emissionCount);
            int _particleCount = emitter.emissionCount;
            static constexpr float _MAG_ = 0.0001f;
            int count = 0;
            for (int y = -sqrt(_particleCount); y < sqrt(_particleCount); y += 2){
                for (int x = -sqrt(_particleCount); x < sqrt(_particleCount); x += 2){
                    float neg_offset = 1 - (Random::GenerateFloat() * 2.0f);
                    float p_offset = (Random::GenerateFloat()) * neg_offset;
                    emitter.offsets[count].x = (float)x / 1000.0f + _MAG_ * p_offset;
                    emitter.offsets[count].y = (float)y / 1000.0f + _MAG_ * p_offset;
                }
            }



        }

}