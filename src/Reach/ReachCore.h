#pragma once
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/Tools/Input/InputManager.h>
#include <Reach/Tools/Scenes/SceneManager.h>


namespace reach{


    class ReachCore{


        public:

            void load();
            void update();
            void render();
            void unload();
            bool isRunning() { return 1;}

    };

}