#pragma once
#include <glad/glad.h>
#include <stdint.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#define SHADER_TYPE_VERTEX      (int) 0x8B31
#define SHADER_TYPE_FRAGMENT    (int) 0x8B30
#define SHADER_TYPE_GEOMETRY    (int) 0x8DD9
#define SHADER_TYPE_TESSELATION (uint8_t)GL_arb_tesselation_shader

namespace reach{

    class ShaderProgram{
        
        private:
            uint32_t _loadShader(const char* fileName, int type);
            uint32_t _shaderProgram;
        public:
            ShaderProgram() = default;
            void loadShader(const char* vertexFile, const char* fragFile);
            void loadShader(const char* vertexFile, const char* fragFile, const char* geomFile);

            void use(){glUseProgram(_shaderProgram);}


    };



}