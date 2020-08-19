#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <Reach/Tools/Logging/Logger.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <entt/entity/registry.hpp>
#include <Reach/ECS/Components.h>

#define REACH_MAX_RENDERABLE 65536
#define REACH_VERTEXDATA_SIZE sizeof(reach::VertexData)
#define REACH_BUFFER_SIZE REACH_MAX_RENDERABLES * REACH_VERTEXDATA_SIZE
#define REACH_INDEX_BUFFER_SIZE REACH_MAX_RENDERABLE * 3
namespace reach{

    struct VertexData{
        
        glm::vec2 position;
        glm::vec4 color;
        glm::vec3 texCoords;

    };

    class BatchRenderer{


        private:
            VertexData* _dataBuffer;
            uint32_t _vertexArrayID, _bufferID, _indexBufferID;
            uint16_t _amountSubmitted;

            void _setBuffer(VertexData data);
            uint16_t _ind[REACH_INDEX_BUFFER_SIZE];


        public:

            BatchRenderer() = default;

            void init();
            void begin();
            void submit(entt::basic_registry<entt::entity>* registry);
            void end();
            void flush();

    };


}