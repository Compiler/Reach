#pragma once
#include <stdint.h>
#include <Reach/Rendering/BatchRenderer.h>
#include <entt/entity/registry.hpp>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/Rendering/ShaderProgram.h>

namespace reach{


    class Scene{


        private:
		    static uint8_t _COUNT;
        
        protected:

            ShaderProgram* _shaderProgram;
		    const char* m_sceneName;
            reach::BatchRenderer* m_renderer;
            entt::basic_registry<entt::entity> m_registry;


        public:
            explicit Scene();
            explicit Scene(const char* name);

            virtual void load();
            virtual void update();
            virtual void render();
            virtual void unload();

            inline const char* getName()const { return m_sceneName; }

    };


}