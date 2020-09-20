#pragma once 

#include <Reach/Tools/Scenes/Layers/Layer.h>
#include <Reach/Tools/Scenes/Scene.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/ECS/Components.h>
#include <Reach/Rendering/TextureManager.h>
#include <Reach/Rendering/ParticleRenderer.h>

#include <Reach/ECS/ParticleSystem.h>
#include <Reach/ECS/PhysicsSystem.h>
#include <Reach/ECS/MovementSystem.h>
namespace reach{


    class DebugBackgroundLayer : public Layer{

        public:
            explicit DebugBackgroundLayer(){
                    m_layerName = "DebugBackgroundLayer";

                    auto ent = m_registry.create();
                    auto& trans = m_registry.emplace<TransformComponent>(ent);
                    trans.position = glm::vec2(0, -0.75);
                    trans.scale = glm::vec2(0.25f);
                    auto& renderable = m_registry.emplace<RenderableComponent>(ent);
                    renderable.color = glm::vec4(1,0,0,1);
                    
                    auto &texComp= m_registry.emplace<TextureComponent>(ent);
                    texComp.bitsPerPixel = 4;
                    texComp.fileName = REACH_INTERNAL_TEXTURE("topgrass.png");
                    TextureManager::registerTexture(texComp);


                    auto ent2 = m_registry.create();
                    auto& trans1 = m_registry.emplace<TransformComponent>(ent2);
                    trans1.position = glm::vec2(-1);
                    trans1.scale = glm::vec2(2);
                    auto& renderable1 = m_registry.emplace<RenderableComponent>(ent2);
                    renderable1.color = glm::vec4(1,0,0,1);
                    
                    auto &texComp1= m_registry.emplace<TextureComponent>(ent2);
                    texComp1.bitsPerPixel = 4;
                    texComp1.fileName = REACH_INTERNAL_TEXTURE("landscape.png");
                    TextureManager::registerTexture(texComp1);

                    
                }

                void load()override{
                    REACH_WARN(m_layerName << " Loading...");

                }
                void update()override{
                    m_systemManager->update(&m_registry);
                }

                void render()override{
                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
                    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
                    m_shaderProgram->use();
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