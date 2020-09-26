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
                auto& particle = emitter.particles[currentParticleIndex];
                float t = particle.timeAlive;
                static glm::vec2 lerpedValue;
                int index1 = (int)(t * emitter.velocities.size());
                int index2 = index1 == emitter.velocities.size()-1 ? index1 * !emitter.cycle : index1 + 1;
                //REACH_DEBUG("Time: " << t  << " (" << t * emitter.velocities.size() << " = " << index1 << ", " << index2 << ")");
                lerpedValue = reach::lerp(emitter.velocities[index1], emitter.velocities[index2], glm::vec2(t));
                particle.position.x += lerpedValue.x;
                particle.position.y += lerpedValue.y;

                index1 = (int)(t * emitter.colors.size());
                index2 = index1 == emitter.colors.size()-1 ? index1 * !emitter.cycle : index1 + 1;
                if(emitter.lerpColors) particle.color =  reach::lerp(emitter.colors[index1], emitter.colors[index2], glm::vec4(t / emitter.colors.size()));
                else particle.color = emitter.colors[index1];

                particle.timeAlive += reach::DELTA_TIME / ((emitter.decayMagnitude) * emitter.decayVariance * Random::GenerateFloat());
                if(particle.timeAlive >= particle.lifeTime){
                    particle.timeDead += reach::DELTA_TIME;
                //particle.timeAlive = particle.lifeTime;
                //particle.active = false;
                
                    particle.timeAlive = 0;
                    particle.timeDead = 0;
                    glm::vec2 spawnOff = reach::lerp(glm::vec2(0),glm::vec2(Random::GenerateFloat(),Random::GenerateFloat()),  emitter.spawnOffset) * (reach::lerp(0,Random::GenerateFloat(),emitter.spawnVariance));
                    particle.position = transform.position + spawnOff;
                    particle.active = true;

                }
                currentParticleIndex++;
            }



        }

}