#pragma once
#include <Reach/Rendering/Window.h>
#include <GLFW/glfw3.h>
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