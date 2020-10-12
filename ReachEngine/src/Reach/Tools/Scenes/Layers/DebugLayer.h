#pragma once 
#include <glm/gtc/type_ptr.hpp>

#include <Reach/Tools/Scenes/Layers/Layer.h>
#include <Reach/Tools/Scenes/Scene.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/Tools/Cameras/OrthographicCamera.h>
#include <Reach/ECS/Components.h>
#include <Reach/Rendering/TextureManager.h>
#include <Reach/Rendering/ParticleRenderer.h>

#include <Reach/ECS/ParticleSystem.h>
#include <Reach/ECS/PhysicsSystem.h>
#include <Reach/ECS/WorldSystem.h>
#include <Reach/ECS/MovementSystem.h>
namespace reach{


    class DebugLayer : public Layer{

        private:
            WorldComponent _world;
            ParticleSystem _updater;
            MovementSystem _movement;
            PhysicsSystem _physics;
            WorldSystem _worldSystem;
            entt::entity p1e;

            ParticleRenderer _system;
            ShaderProgram _particleShader;

            OrthographicCamera cam;

        public:

        

        explicit DebugLayer(){
                m_layerName = "Debug Scene";

                cam = OrthographicCamera(0, 0, 1920, 1080);
                cam.update();
                m_shaderProgram->loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));
                m_shaderProgram->use();
                m_shaderProgram->uniform_set1Mat4("u_cameraMatrix", &cam.getCombined()[0][0]);
                
                _particleShader.loadShader(REACH_INTERNAL_SHADER("particle_pass.vert"), REACH_INTERNAL_SHADER("particle_pass.frag"));
                _particleShader.use();
                _particleShader.uniform_set1Mat4("u_cameraMatrix", &cam.getCombined()[0][0]);
                constexpr float _SZ_ = 50;
                auto ee = addEntity(800, 500, glm::vec2(1), 0, 0, 1, "src/Resources/Textures/wall.jpg", 3, true);
                auto eee = addEntity(300, 500, glm::vec2(_SZ_), 0, 0, 1, "src/Resources/Textures/pixeldirt.png", 4, true);
                auto eeee = addEntity(1900, 500, glm::vec2(_SZ_), 0, 0, 1, "src/Resources/Textures/wall.jpg", 3, true);
                addParticleEmitter(ee);
                p1e = ee;
                auto& movement = m_registry.emplace<MovementComponent>(ee, MovementComponent());
                float m = 2.5f;
                movement.set(KeyCodes::KEY_A, glm::vec2(-m, 0 ));
                movement.set(KeyCodes::KEY_D, glm::vec2(m, 0 ));
                movement.set(KeyCodes::KEY_W, glm::vec2(0, m));
                movement.set(KeyCodes::KEY_S, glm::vec2(0, -m ));

                for(int i = 0; i < cam.getWidth(); i += (cam.getWidth() / 4)){
                    addEntity(i, 0, glm::vec2(1, 100000), 0, 0, 1, "src/Resources/Textures/wall.jpg", 3);
                    REACH_DEBUG(i << ", 0)");

                }

                for(int i = 0; i < cam.getHeight(); i += (cam.getHeight() / 4)){
                    addEntity(0, i, glm::vec2(1000000, 1), 0, 0, 1, "src/Resources/Textures/wall.jpg", 3);
                    REACH_DEBUG("(0," << i);
                }
                
                _system.init();

                m_systemManager->addSystem(&_updater);
                m_systemManager->addSystem(&_movement);
                m_systemManager->addSystem(&_physics);
                m_systemManager->addSystem(&_worldSystem);



                auto worldEntity = m_registry.create();
                auto& w = m_registry.emplace<WorldComponent>(worldEntity);
                w.worldCamera = &cam;
                _world = w;

            }
            void addParticleEmitter(entt::entity e){
                auto& particleComp = m_registry.emplace<reach::ParticleEmitterComponent>(e, ParticleEmitterComponent());
                particleComp.decayVariance = 0.250f;
                particleComp.decayMagnitude= 1000.0f;

                particleComp.spawnOffset = glm::vec2(1);
                particleComp.spawnVariance = 10;


                float v = 15.75f;
                constexpr int COUNTER = 50000;
                for(int i = 0; i < COUNTER; i++){
                    particleComp.addVelocityWeight(glm::vec2(-v / 2.0f, v), 1);
                    particleComp.addVelocityWeight(glm::vec2(v / 2.0f, v), 1);
                }
                particleComp.addVelocityWeight(glm::vec2(-v / 2.0f, v/5), 1);
                particleComp.addVelocityWeight(glm::vec2(v / 2.0f, v/5), 1);

                particleComp.colors.push_back(glm::vec4(1.0, 0.2, 0.0, 1));
                particleComp.addColorWeight(glm::vec4(1.0, 0.4, 0.1, 1), 2);
                particleComp.addColorWeight(glm::vec4(0.6, 0.3, 0.1, 0.8), 2);
                particleComp.addColorWeight(glm::vec4(0.2, 0.2, 0.2, 0.2), 3);
                

                particleComp.emissionCount = REACH_MAX_RENDERABLE / 4 - 1;
                particleComp.cycle = true;
                particleComp.lerpColors = true;
                REACH_DEBUG("created emitter '" << particleComp._db_name << "'");

            }
            entt::entity addEntity(float x, float y, glm::vec2 s = glm::vec2(1), float r = 1, float g = 1, float b = 1, const char* str = "tdirt.png", int bpp = 3, bool col = false){
                auto currentEntity = m_registry.create();
                //REACH_DEBUG("Created entity");
                auto &pos = m_registry.emplace<TransformComponent>(currentEntity, TransformComponent());
                pos.position = glm::vec2(x, y);
                pos.scale = glm::vec2(s);
                if(col)
                    auto& collidable = m_registry.emplace<reach::CollidableComponent>(currentEntity, CollidableComponent());

                auto &rend = m_registry.emplace<RenderableComponent>(currentEntity, RenderableComponent());
                rend.color = glm::vec4(r,g,b,1.0f);

                auto &texComp= m_registry.emplace<TextureComponent>(currentEntity, TextureComponent());
                static bool flip = true;
                texComp.bitsPerPixel = bpp;
                texComp.fileName = str;
                flip = !flip;

               

                TextureManager::registerTexture(texComp);//TODO: THIS IS RELOADING A TEXTURE EVERY CALL
                return currentEntity;



            }


            void load()override{
                REACH_WARN(m_layerName << " Loading...");

            }
            void update()override{
                cam.update();
                
                m_systemManager->update(&m_registry);
            }

             void render()override{
                _particleShader.use();
                //_particleShader.uniform_set1Mat4("u_cameraMatrix", &cam.getCombined()[0][0]);
                _system.begin();
                _system.submit(&m_registry);
                _system.end();
                _system.flush();

                m_shaderProgram->use();
                //m_shaderProgram->uniform_set1Mat4("u_cameraMatrix", &cam.getCombined()[0][0]);
                m_renderer->begin();
                m_renderer->submit(&m_registry);
                m_renderer->end();
                m_renderer->flush();
            }
            void unload()override{
                REACH_WARN(m_layerName << " Unloaded...");
            }

    };

}