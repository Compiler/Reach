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
                float t = emitter.particles[currentParticleIndex].timeAlive;
                static glm::vec2 lerpedValue;
                int index1 = (int)(t * emitter.velocities.size());
                int index2 = index1 == emitter.velocities.size()-1 ? index1 : index1 + 1;
                lerpedValue = reach::lerp(emitter.velocities[index1], emitter.velocities[index2], glm::vec2(t));
                emitter.particles[currentParticleIndex].position.x += lerpedValue.x;
                emitter.particles[currentParticleIndex].position.y += lerpedValue.y;

                index1 = (int)(t * emitter.colors.size());
                index2 = index1 == emitter.colors.size()-1 ? index1 : index1 + 1;
                emitter.particles[currentParticleIndex].color =  reach::lerp(emitter.colors[index1], emitter.colors[index2], glm::vec4(t));
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