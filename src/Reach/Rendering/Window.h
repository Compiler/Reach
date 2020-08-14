#pragma once
#include <Reach/Tools/Logging/Logger.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace reach{

    class Window{

        private:
            const char* _windowName;
            GLFWwindow* _window;
        public:
            static float SCREEN_WIDTH;
            static float SCREEN_HEIGHT;

            Window() = default;
            Window(float width, float height, const char* name, bool fullscreen = false);


            GLFWwindow* getWindow()const{return _window;}

    };


}