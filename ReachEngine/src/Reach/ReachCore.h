#pragma once
#include <glad/glad.h>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/Rendering/Window.h>
#include <entt/entity/registry.hpp>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/Tools/Scenes/DebugScene.h>
#include <Reach/Tools/Scenes/SceneManager.h>
#define ENTT_STANDALONE
#include <Reach/Tools/Startup/StartupSystems.h>
#include <glm/vec3.hpp>
#include <Reach/Tools/Callbacks/GLFWCallbacks.h>
#include <Reach/Reach.h>
#include <chrono>
// #include <imgui/imgui.h>
// #include <imgui/imgui_impl_opengl3.h>
// #include <imgui/imgui_impl_glfw.h>

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
