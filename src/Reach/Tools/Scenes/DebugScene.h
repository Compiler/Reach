#pragma once
#include <Reach/Tools/Scenes/Scene.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/ECS/Components.h>
#include <Reach/Rendering/TextureManager.h>
#include <Reach/Rendering/ParticleSystem.h>


namespace reach{

    class DebugScene : public Scene{
        private:
            glm::vec4 col = glm::vec4(0.4, 0.2, 0.4, 1.0);
            ParticleSystem _system;
            ShaderProgram _particleShader;
            entt::entity e;
            reach::TransformComponent* pos;

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

                _shaderProgram = new ShaderProgram();
                _shaderProgram->loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));

                _particleShader = ShaderProgram();
                _particleShader.loadShader(REACH_INTERNAL_SHADER("particle_pass.vert"), REACH_INTERNAL_SHADER("particle_pass.frag"));

                addEntity(-0.05,  -0.05, 0.10f, 0, 0, 1, "src/Resources/Textures/wall.jpg", 3);
                //addEntity(0.1 , -0.9, 0.25f, 1, 0, 0, "src/Resources/Textures/tdirt.png", 4);

                _system.init(TextureComponent());

                //_loadChunk(0);
                //_loadChunk(1);
                //_loadChunk(3);

            }
            void addEntity(float x, float y, float s = 1.0f, float r = 1, float g = 1, float b = 1, const char* str = "tdirt.png", int bpp = 3){
                e = m_registry.create();
                REACH_DEBUG("Created entity");
                pos = &m_registry.emplace<TransformComponent>(e, TransformComponent());
                pos->position = glm::vec2(x, y);
                pos->scale = glm::vec2(s);

                auto &rend = m_registry.emplace<RenderableComponent>(e, RenderableComponent());
                rend.color = glm::vec4(r,g,b,1.0f);

                auto &texComp= m_registry.emplace<TextureComponent>(e, TextureComponent());
                static bool flip = true;
                texComp.bitsPerPixel = bpp;
                texComp.fileName = str;
                flip = !flip;
                TextureManager::_dbg_printTextureSlots();
                TextureManager::registerTexture(texComp);
                TextureManager::_dbg_printTextureSlots();



            }
            void _set_color_(float r, float g, float b, float a){col = glm::vec4(r,g,b,a);}

            void load()override{
                REACH_WARN(m_sceneName << " Loading...");

            }
            void update()override{

                if(InputManager::isKeyPressed(KeyCodes::KEY_D)) {
                    pos->position.x += 0.0001f;
                    REACH_LOG("Moving!");
                    //auto& c = m_registry.get<TransformComponent>(e);
                    //c.position.x += 0.0001f;
                }

            }
            void render()override{
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
                glClearColor(col.r, col.g, col.b, col.a);

                //_particleShader.use();
                //_system.begin();
                //_system.submit(&m_registry);
                //_system.end();
                //_system.flush();
                _shaderProgram->use();
                m_renderer->begin();
                m_renderer->submit(&m_registry);
                m_renderer->end();
                m_renderer->flush();

            }
            void unload()override{
                REACH_WARN(m_sceneName << " Unloaded...");

            }

    };


}