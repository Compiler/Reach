#pragma once
#include <stdint.h>
#include <Reach/Rendering/BatchRenderer.h>
#include <entt/entity/registry.hpp>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/Rendering/ShaderProgram.h>
#include <Reach/ECS/SystemManager.h>
#include <Box2D/box2d.h>
namespace reach{


    class Scene{


        private:
		    static uint8_t _COUNT;
        
        protected:

            ShaderProgram* m_shaderProgram;
            SystemManager* m_systemManager;
		    const char* m_sceneName;
            reach::BatchRenderer* m_renderer;
            entt::basic_registry<entt::entity> m_registry;

    //may not be initialized in every scene
        protected:
            b2World* m_world;


        public:
            explicit Scene();
            explicit Scene(const char* name);

            virtual void load();
            virtual void update();
            virtual void render();
            virtual void unload();

            void setName(const char* name) {m_sceneName = name;};
            inline const char* getName()const { return m_sceneName; }

    };


}