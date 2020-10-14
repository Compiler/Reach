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

        private:
            OrthographicCamera cam;


        public:
            explicit DebugBackgroundLayer(){
                    m_layerName = "DebugBackgroundLayer";
                    m_shaderProgram->loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("dimmer.frag"));
                     cam = OrthographicCamera(0, 0, 1920, 1080);
                    cam.update();
                    m_shaderProgram->use();
                    m_shaderProgram->uniform_set1Float("u_dimmer", 0.4f);
                    m_shaderProgram->uniform_set1Mat4("u_cameraMatrix", &cam.getCombined()[0][0]);
                    auto ent = m_registry.create();
                    auto& trans = m_registry.emplace<TransformComponent>(ent);
                    trans.position = glm::vec2(0,0);
                    trans.scale = glm::vec2(100,100);
                    auto& renderable = m_registry.emplace<RenderableComponent>(ent);
                    renderable.color = glm::vec4(1,0,0,1);
                    
                    auto &texComp= m_registry.emplace<TextureComponent>(ent);
                    texComp.bitsPerPixel = 4;
                    texComp.fileName = REACH_INTERNAL_TEXTURE("topgrass.png");
                    TextureManager::registerTexture(texComp);


                    auto ent2 = m_registry.create();
                    auto& trans1 = m_registry.emplace<TransformComponent>(ent2);
                    trans1.position = glm::vec2(0);
                    trans1.scale = glm::vec2(2400,1920);
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
                    static int count = 0;
                    //count++;
                    //assert(count < 3);
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