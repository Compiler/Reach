#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
namespace reach{

    struct NameComponent{

        const char* name;

    };

    struct TransformComponent{

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

    };

    struct RenderableComponent{

        glm::vec4 color;

    };
}