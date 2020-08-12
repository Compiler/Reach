#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace reach{

    class Window{

        private:
            std::string _windowName;
            GLFWwindow* _window;
        public:
            static float SCREEN_WIDTH;
            static float SCREEN_HEIGHT;

            Window(float width, float height, const char name[], bool fullscreen = false);


            GLFWwindow* getWindow()const{return _window;}

    };


}