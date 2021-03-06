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
#include <Reach/Tools/Input/InputManager.h>
#include <Reach/Rendering/TextureManager.h>
#include <unordered_map>
#define REACH_MAX_RENDERABLE 65536
#define REACH_VERTEXDATA_SIZE sizeof(reach::VertexData)
#define REACH_BUFFER_SIZE REACH_MAX_RENDERABLES * REACH_VERTEXDATA_SIZE
#define REACH_INDEX_BUFFER_SIZE REACH_MAX_RENDERABLE 
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
            uint32_t _amountSubmitted;
            uint16_t _ind[REACH_INDEX_BUFFER_SIZE];

            void _setBuffer(VertexData& data);


        public:

            BatchRenderer() = default;

            void init();
            void begin();
            void submit(entt::basic_registry<entt::entity>* registry);
            void end();
            void flush();

    };


}