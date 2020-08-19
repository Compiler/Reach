#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/Rendering/TextureManager.h>
namespace reach{
    //static class
    class StartupSystems{
        public:
            static void _initGLFW();
            static void _initGlad();
            static void _initTextureManager();
            StartupSystems() = delete;
            StartupSystems operator=(const StartupSystems&) = delete;
            static void initSubSystems();
    };
}