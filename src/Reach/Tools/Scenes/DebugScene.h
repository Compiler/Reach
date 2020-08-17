#pragma once 
#include <Reach/Tools/Scenes/Scene.h>

namespace reach{

    class DebugScene : public Scene{

            glm::vec4 col = glm::vec4(0.4, 0.2, 0.4, 1.0);

        public:
            
            explicit DebugScene(){
                Scene();
                m_sceneName = "Debug Scene";

                auto e = m_registry.create();
                auto &pos = m_registry.emplace<TransformComponent>(e, TransformComponent());
                pos.position = glm::vec2(-0.5f, -0.5f);
                pos.scale = glm::vec2(1, 1);
                REACH_LOG("Pos: (" << pos.position.x << ", "<< pos.position.y << ")");
                pos.position.x = -0.25;
                pos.scale = glm::vec2(1,1);
                REACH_LOG("Pos: (" << pos.position.x << ", "<< pos.position.y << ")");

                auto &rend = m_registry.emplace<RenderableComponent>(e, RenderableComponent());
                rend.color = glm::vec4(1,0,1,1);
                _shaderProgram = new ShaderProgram();
                _shaderProgram->loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));

            }

            void _set_color_(float r, float g, float b, float a){}

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