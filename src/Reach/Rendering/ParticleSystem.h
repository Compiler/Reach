#pragma once
#include <glad/glad.h>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/ECS/Components.h>
#include <entt/entity/registry.hpp>
#include <Reach/Rendering/TextureManager.h>
#define REACH_MAX_RENDERABLE 65536
#define REACH_VERTEXDATA_SIZE sizeof(reach::ParticleVertexData)
#define REACH_BUFFER_SIZE REACH_MAX_RENDERABLES * REACH_VERTEXDATA_SIZE
#define REACH_INDEX_BUFFER_SIZE REACH_MAX_RENDERABLE 

namespace reach{

    struct ParticleVertexData{
        
        glm::vec2 position;

    };


    class ParticleSystem{

        private:
            uint32_t _vertexArrayID, _bufferID, _instancedBufferID, _indexBufferID;
            uint32_t _amountSubmitted;
            uint16_t* _indices;
            ParticleVertexData* _dataBuffer;

            void _setBuffer(ParticleVertexData& data);



        public:

            ParticleSystem() = default;

            void init(TextureComponent particles);
            void begin();
            void submit(entt::basic_registry<entt::entity>* registry);
            void end();
            void flush();

    };

}