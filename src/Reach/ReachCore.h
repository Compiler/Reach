#pragma once
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/Rendering/Window.h>
#include <entt/entity/registry.hpp>
#include <Reach/ECS/Components.h>
#define ENTT_STANDALONE
#include <Reach/Tools/Startup/StartupSystems.h>
#include <glm/vec3.hpp>

namespace reach{


    class ReachCore{

        private:

            reach::Window* _windowRef;



        public:

            void load();
            void update();
            void render();
            void unload();
            bool isRunning() { return 1;}

    };

}