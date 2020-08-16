#pragma once
#include <glad/glad.h>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/Rendering/Window.h>
#include <entt/entity/registry.hpp>
#include <entt/entity/runtime_view.hpp>
#include <vector>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/ECS/Components.h>
#define ENTT_STANDALONE
#include <Reach/Tools/Startup/StartupSystems.h>
#include <glm/vec3.hpp>
#include <Reach/Rendering/BatchRenderer.h>

namespace reach{


    class ReachCore{

        private:

            reach::Window* _windowRef;
            reach::BatchRenderer* _renderer;
            entt::basic_registry<entt::entity> _registry;
            unsigned int _shaderProgram;

            void loadShaders(const char* vertexFile, const char* fragmentFile);


        public:

            void load();
            void update();
            void render();
            void unload();
            bool isRunning() { return 1;}

    };

}
