#pragma once
#include <glad/glad.h>
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/ECS/Components.h>

namespace reach{


    struct ParticleVertexData{
        
        glm::vec2 position;
        glm::vec4 color;

    };


    class ParticleSystem{

        private:
            uint32_t _vertexArrayID, _bufferID, _instancedBufferID, _indexBufferID;
            uint32_t _amountSubmitted;

            uint16_t* _indices;


        public:

            ParticleSystem() = default;

            void init(TextureComponent particles);
            void begin();
            void submit();
            void end();
            void flush();

    };

}