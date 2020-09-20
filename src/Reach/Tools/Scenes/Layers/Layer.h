#pragma once
#include <Reach/Rendering/BatchRenderer.h>
#include <entt/entity/registry.hpp>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/Rendering/ShaderProgram.h>
#include <Reach/ECS/SystemManager.h>

namespace reach{


    class Layer{

        private:
            static uint16_t _COUNT;
        protected:
            const char* m_layerName;

            SystemManager* m_systemManager;
            reach::BatchRenderer* m_renderer;
            ShaderProgram* m_shaderProgram;
            entt::basic_registry<entt::entity> m_registry;

            glm::vec4 m_clearColor = glm::vec4(0.1);


        public:
            explicit Layer();
            explicit Layer(const char* name);

            virtual void load();
            virtual void update();
            virtual void render();
            virtual void unload();

            const char* getName(){return m_layerName;}

            void setClearColor(glm::vec4 color);

    };

}