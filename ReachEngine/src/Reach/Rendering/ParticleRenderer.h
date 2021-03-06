#pragma once
#include <glad/glad.h>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/ECS/Components.h>
#include <entt/entity/registry.hpp>
#include <Reach/Rendering/TextureManager.h>
#include <Reach/Tools/Utils/Random.h>
#define REACH_MAX_RENDERABLE 65536 * 4
#define REACH_VERTEXDATA_SIZE sizeof(reach::ParticleVertexData)
#define REACH_BUFFER_SIZE REACH_MAX_RENDERABLES * REACH_VERTEXDATA_SIZE
#define REACH_INDEX_BUFFER_SIZE REACH_MAX_RENDERABLE 

namespace reach{

    struct ParticleInstancedData{
        glm::vec2 offset;
        glm::vec4 color;

    };

    struct ParticleVertexData{
        
        glm::vec2 position;

    };


    class ParticleRenderer{
        private:
            uint32_t _vertexArrayID, _bufferID, _instancedBufferID, _indexBufferID;
            uint32_t _amountSubmitted, _instancesCreated;
            uint16_t* _indices;
            ParticleInstancedData* _instancedDataBuffer;
            ParticleVertexData * _vertexDataBuffer;

            void _setBuffer(ParticleVertexData& buffer);



        public:

            ParticleRenderer() = default;

            void init();
            void begin();
            void submit(entt::basic_registry<entt::entity>* registry);
            void end();
            void flush();

    };

}