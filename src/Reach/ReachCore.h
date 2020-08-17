#pragma once
#include <glad/glad.h>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/Rendering/Window.h>
#include <entt/entity/registry.hpp>
#include <entt/entity/runtime_view.hpp>
#include <vector>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/ECS/Components.h>
#include <Reach/Tools/Scenes/DebugScene.h>
#include <Reach/Tools/Scenes/SceneManager.h>
#define ENTT_STANDALONE
#include <Reach/Tools/Startup/StartupSystems.h>
#include <glm/vec3.hpp>
#include <Reach/Rendering/BatchRenderer.h>
#include <Reach/Tools/Callbacks/GLFWCallbacks.h>

namespace reach{


    class ReachCore{

        private:
            SceneManager _sceneManager;
            reach::Window* _windowRef;
            float msPerFrame = 0, previousMSPerFrame = 0, accumMSFPS = 0;
            float framesPerSecond = 0;
            bool _running = true;

            void loadShaders(const char* vertexFile, const char* fragmentFile);


        public:

            void load();
            void update();
            void render();
            void unload();
            bool isRunning() { return _running;}

    };

}
