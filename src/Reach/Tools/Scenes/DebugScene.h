#pragma once 
#include <Reach/Tools/Scenes/Scene.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/ECS/Components.h>


namespace reach{

    class DebugScene : public Scene{
        private:
            glm::vec4 col = glm::vec4(0.4, 0.2, 0.4, 1.0);
            TextureComponent* comp;


            void _loadChunk(int id){
                static float C_SZ = 1;
                static float offset = 0.25f;
                for(float x = 0; x < C_SZ; x+=offset){
                    for(float y = -1; y < C_SZ - 1; y+=offset){
                        float initOffset = id*C_SZ;
                        addEntity(initOffset + x, initOffset + y, 0.25f);
                    }
                }

            }
        public:
            
            explicit DebugScene(){
                m_sceneName = "Debug Scene";

                _shaderProgram = new ShaderProgram();
                _shaderProgram->loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));

                addEntity(-1, -1, 1, 1, 0, 0);
                addEntity(0 , -1, 1, 1, 0, 0);
               // _loadChunk(0);
               // _loadChunk(2);
               //_loadChunk(-2);

            }
            void addEntity(float x, float y, float s = 1.0f, float r = 1, float g = 1, float b = 1){
                auto e = m_registry.create();
                REACH_DEBUG("Created entity");
                auto &pos = m_registry.emplace<TransformComponent>(e, TransformComponent());
                pos.position = glm::vec2(x, y);
                pos.scale = glm::vec2(1, 1);

                auto &rend = m_registry.emplace<RenderableComponent>(e, RenderableComponent());
                rend.color = glm::vec4(r,g,b,1.0f);

                auto &texComp= m_registry.emplace<TextureComponent>(e, TextureComponent());

                texComp.fileName = REACH_INTERNAL_TEXTURE("tdirt.png");
                texComp.bitsPerPixel = 4;
                FileLoaderFactory::loadOpenGLTexture(&texComp);



            }
            void _set_color_(float r, float g, float b, float a){col = glm::vec4(r,g,b,a);}

            void load()override{
                REACH_WARN(m_sceneName << " Loading...");
            
                //loadShaders(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));


            }
            void update()override{}
            void render()override{
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
                glClearColor(col.r, col.g, col.b, col.a);

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