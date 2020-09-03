#pragma once
#include <Reach/Tools/Scenes/Scene.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/ECS/Components.h>
#include <Reach/Rendering/TextureManager.h>
#include <Reach/Rendering/ParticleRenderer.h>

#include <Reach/ECS/ParticleSystem.h>
#include <Reach/ECS/MovementSystem.h>

namespace reach{

    class DebugScene : public Scene{
        private:
            ParticleSystem _updater;
            MovementSystem _movement;
            ParticleEmitterComponent* particleComp;
        private:
            glm::vec4 col = glm::vec4(0.4, 0.2, 0.4, 1.0);
            ParticleRenderer _system;
            ShaderProgram _particleShader;

            void _loadChunk(int id){
                static float C_SZ = 0.25f;
                static float offset = 0.05f;
                for(float x = 0; x < C_SZ; x+=offset){
                    for(float y = -1; y < C_SZ - 1; y+=offset){
                        float initOffset = id*C_SZ;
                        addEntity(initOffset + x, initOffset + y, offset, 1, 0, 0, "src/Resources/Textures/tdirt.png", 4);
                    }
                }

            }
        public:

            explicit DebugScene(){
                m_sceneName = "Debug Scene";

                m_shaderProgram = new ShaderProgram();
                m_shaderProgram->loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));
                _particleShader = ShaderProgram();
                _particleShader.loadShader(REACH_INTERNAL_SHADER("particle_pass.vert"), REACH_INTERNAL_SHADER("particle_pass.frag"));
                auto entity  = addEntity(0, 0, 0.0025f, 0, 0, 1, "src/Resources/Textures/wall.jpg", 3);
                auto movement = &m_registry.emplace<MovementComponent>(entity, MovementComponent());
                float m = 0.001f;
                movement->set(KeyCodes::KEY_A, glm::vec2(-m, 0 ));
                movement->set(KeyCodes::KEY_D, glm::vec2(m, 0 ));
                movement->set(KeyCodes::KEY_W, glm::vec2(0, m));
                movement->set(KeyCodes::KEY_S, glm::vec2(0, -m ));
                //addEntity(0.1 , -0.9, 0.25f, 1, 0, 0, "src/Resources/Textures/tdirt.png", 4);

                _system.init();

                m_systemManager->addSystem(&_updater);
                m_systemManager->addSystem(&_movement);

            }
            entt::entity addEntity(float x, float y, float s = 1.0f, float r = 1, float g = 1, float b = 1, const char* str = "tdirt.png", int bpp = 3){
                auto e = m_registry.create();
                //REACH_DEBUG("Created entity");
                auto pos = &m_registry.emplace<TransformComponent>(e, TransformComponent());
                pos->position = glm::vec2(x, y);
                pos->scale = glm::vec2(s);

                auto &rend = m_registry.emplace<RenderableComponent>(e, RenderableComponent());
                rend.color = glm::vec4(r,g,b,1.0f);

                auto &texComp= m_registry.emplace<TextureComponent>(e, TextureComponent());
                static bool flip = true;
                texComp.bitsPerPixel = bpp;
                texComp.fileName = str;
                flip = !flip;

                particleComp = &m_registry.emplace<reach::ParticleEmitterComponent>(e, ParticleEmitterComponent());
                particleComp->decayVariance = 2.0f;
                particleComp->decayMagnitude= 1000.0f;

                particleComp->spawnOffset = glm::vec2(0.05, 0.02);
                particleComp->spawnVariance = 0.0f;


                float v = 0.00025f;
                particleComp->addVelocityWeight(glm::vec2(v, 0), 1);
                particleComp->addVelocityWeight(glm::vec2(0, v*4), 1);
                particleComp->addVelocityWeight(glm::vec2(-v*4, 0), 1);
                particleComp->addVelocityWeight(glm::vec2(0, -v * 4), 1);

                particleComp->colors.push_back(glm::vec4(0.5, 0.2, 0.1, 1));
                particleComp->colors.push_back(glm::vec4(0.0, 0.0, 1.0, 1));
                particleComp->colors.push_back(glm::vec4(0.0, 1.0, 0.0, 1));
                particleComp->colors.push_back(glm::vec4(1.0, 0.0, 0.0, 1));

                particleComp->emissionCount = 8192;
                TextureManager::registerTexture(texComp);//TODO: THIS IS RELOADING A TEXTURE EVERY CALL
                return e;



            }
            void _set_color_(float r, float g, float b, float a){col = glm::vec4(r,g,b,a);}

            void load()override{
                REACH_WARN(m_sceneName << " Loading...");

            }
            void update()override{

                m_systemManager->update(&m_registry);

            }
            void render()override{
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
                glClearColor(col.r, col.g, col.b, col.a);
                if(InputManager::isKeyPressed(KeyCodes::KEY_LEFT))  particleComp->decayVariance -= 0.02f * reach::DELTA_TIME;
                if(InputManager::isKeyPressed(KeyCodes::KEY_RIGHT))  particleComp->decayVariance += 0.02f * reach::DELTA_TIME;

                if(InputManager::isKeyPressed(KeyCodes::KEY_T))  particleComp->decayMagnitude -= 2.f * reach::DELTA_TIME;
                if(InputManager::isKeyPressed(KeyCodes::KEY_Y))  particleComp->decayMagnitude += 2.f * reach::DELTA_TIME;

                if(InputManager::isKeyReleased(KeyCodes::KEY_SPACE))  particleComp->cycle = !particleComp->cycle;
                if(particleComp->decayVariance <= 0) particleComp->decayVariance = 0.000000001f;
                _particleShader.use();
                _system.begin();
                _system.submit(&m_registry);
                _system.end();
                _system.flush();
                //m_shaderProgram->use();
                //m_renderer->begin();
                //m_renderer->submit(&m_registry);
                //m_renderer->end();
                //m_renderer->flush();

            }
            void unload()override{
                REACH_WARN(m_sceneName << " Unloaded...");

            }

    };


}