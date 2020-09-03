#include "ParticleSystem.h"



void reach::ParticleSystem::update(entt::basic_registry<entt::entity>* registry){
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
                //float neg1 = 1 - (Random::GenerateFloat() * 2.0f);
                //float neg2 = 1 - (Random::GenerateFloat() * 2.0f);
                float t = emitter.particles[currentParticleIndex].timeAlive;
                static glm::vec2 lerpedValue;
                lerpedValue = reach::lerp(emitter.startingVelocity, emitter.endingVelocity, glm::vec2(t));
                emitter.particles[currentParticleIndex].position.x += lerpedValue.x;
                emitter.particles[currentParticleIndex].position.y += lerpedValue.y;
                
                emitter.particles[currentParticleIndex].color = reach::lerp(emitter.startingColor, emitter.endingColor, glm::vec4(t));
                emitter.particles[currentParticleIndex].timeAlive += reach::DELTA_TIME / (10000.0f * Random::GenerateFloat());
                if(emitter.particles[currentParticleIndex].timeAlive >= emitter.particles[currentParticleIndex].lifeTime){
                //emitter.particles[currentParticleIndex].timeAlive = emitter.particles[currentParticleIndex].lifeTime;
                //emitter.particles[currentParticleIndex].active = false;
                
                emitter.particles[currentParticleIndex].timeAlive = 0;
                emitter.particles[currentParticleIndex].position = emitter.anchorPosition;
                emitter.particles[currentParticleIndex].active = true;

                }
                currentParticleIndex++;
            }



        }

}