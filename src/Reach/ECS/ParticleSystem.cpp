#include "ParticleSystem.h"



void reach::ParticleSystem::update(entt::basic_registry<entt::entity>* registry, float deltaTime){
        auto renderables = registry->view<TransformComponent, RenderableComponent, ParticleEmitterComponent>();
        double current = glfwGetTime();
        double elapsed = glfwGetTime() - current;
        for(auto entity: renderables) {
            reach::TransformComponent &transform = renderables.get<TransformComponent>(entity);
            reach::RenderableComponent &renderable = renderables.get<RenderableComponent>(entity);
            reach::ParticleEmitterComponent &emitter = renderables.get<ParticleEmitterComponent>(entity);
            if(emitter.particles.size() != emitter.emissionCount) emitter.particles.resize(emitter.emissionCount);
            static constexpr float _MAG_ = 0.0001f;
            for (int currentParticleIndex = 0; currentParticleIndex < emitter.emissionCount; currentParticleIndex++){
                    float neg_offset = 1 - (Random::GenerateFloat() * 2.0f);
                    float p_offset = (Random::GenerateFloat()) * neg_offset;
                    emitter.particles[currentParticleIndex].position.x += emitter.startingVelocity.x * p_offset;
                    emitter.particles[currentParticleIndex].position.y += emitter.startingVelocity.y * p_offset;
                    emitter.particles[currentParticleIndex].timeAlive += reach::DELTA_TIME / (100000.0f * Random::GenerateFloat());
                   // REACH_LOG("Time alive: " << emitter.particles[currentParticleIndex].timeAlive << " -- life time allowed to live " << emitter.particles[currentParticleIndex].lifeTime);
                    if(emitter.particles[currentParticleIndex].timeAlive >= emitter.particles[currentParticleIndex].lifeTime){
                        emitter.particles[currentParticleIndex].active = false;
                       // REACH_WARN("Particle #" << currentParticleIndex << " is dead.");
                    }
                    currentParticleIndex++;
            }



        }

}