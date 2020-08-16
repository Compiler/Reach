#pragma once
#include <string>
#include <fstream>
#include <streambuf>
#include <Reach/Tools/Logging/Logger.h>
#define REACH_INTERNAL(x)         "src/Resources/" x
#define REACH_INTERNAL_SHADER(x)  REACH_INTERNAL("Shaders/") x
#define REACH_INTERNAL_TEXTURE(x) REACH_INTERNAL("Textures/") x
#define REACH_INTERNAL_MODEL(x)   REACH_INTERNAL("Models/") x
#define REACH_INTERNAL_SOUNDS(x)  REACH_INTERNAL("Sounds/") x


namespace reach {

    namespace FileLoaderFactory{
        extern void loadTextFromFile(const char fileName[], std::string& dst);
        //rgba default composition
        extern unsigned char* loadImage(const char name[], int* width, int* height, int* numOfColChannels, int req_comp = 4/*STBI_rgb_alpha = 4*/);
        extern void free(void* data);
    }
}