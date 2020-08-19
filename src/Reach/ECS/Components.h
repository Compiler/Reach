#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
namespace reach{


    uint64_t hash_name(const char* str);

    struct NameComponent{

        const char* name;

    };

    struct TransformComponent{

        glm::vec2 position;
        glm::vec2 rotation;
        glm::vec2 scale;

        TransformComponent(){}
        TransformComponent(float x, float y): position(glm::vec2(x,y)){}

    };

    struct RenderableComponent{

        glm::vec4 color;

    };
    struct TextureComponent{

        uint32_t id = -1;
        uint64_t keyFileName = -1;
        uint32_t bitsPerPixel = 0;
        const char* fileName;

    };
}