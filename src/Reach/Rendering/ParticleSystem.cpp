#include "ParticleSystem.h"

namespace reach{


    void ParticleSystem::init(TextureComponent particle){

            REACH_LOG("ParticleSystem initializing...");
            glGenVertexArrays(1, &_vertexArrayID);
            glBindVertexArray(_vertexArrayID);
            glm::vec2 translations[100];
            int index = 0;
            float offset = 0.01f;
            for (int y = -10; y < 10; y += 2)
            {
                for (int x = -10; x < 10; x += 2)
                {
                    glm::vec2 translation;
                    translation.x = (float)x / 10.0f + offset;
                    translation.y = (float)y / 10.0f + offset;
                    translations[index++] = translation;
                }
            }

            glGenBuffers(1, &_instancedBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, _instancedBufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleInstancedData) * REACH_MAX_RENDERABLE, NULL, GL_DYNAMIC_DRAW);
            //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glGenBuffers(1, &_bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleVertexData) * REACH_MAX_RENDERABLE, NULL, GL_DYNAMIC_DRAW);
            
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertexData), (const void*)  0                  ); // POSITION
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertexData), (const void*) (2 * sizeof(float)) ); // COLOUR

            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, _instancedBufferID);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexAttribDivisor(2, 1); 

            _indices = new uint16_t[100];
            for(uint16_t i = 0; i < 100; i ++) _indices[i] = i;
            _indices[3] = 0; _indices[4] = 1;_indices[5] = 5;
            glGenBuffers(1, &_indexBufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);
            glBindVertexArray(0);
            _passedBufferState.reserve(1000);
    }

    void ParticleSystem::begin(){
        //setup dynamic buffer - profile speed gap
        glBindBuffer(GL_ARRAY_BUFFER, _instancedBufferID);
        _instancedDataBuffer = (reach::ParticleInstancedData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        _amountSubmitted = 0;

        float offset = 0.0001f;
            for (int y = -15; y < 15; y += 2)
            {
                for (int x = -15; x < 15; x += 2)
                {
                    ParticleInstancedData datum;
                    float neg_offset = 1 - (Random::GenerateFloat() * 2.0f);
                    float p_offset = (Random::GenerateFloat()) * neg_offset;
                    datum.offset.x = (float)x / 1000.0f + offset * p_offset;
                    datum.offset.y = (float)y / 1000.0f + offset * p_offset;
                    _passedBufferState[_amountSubmitted].offset += datum.offset * (1.0f - Random::GenerateFloat() * 2.0f);

                    _instancedDataBuffer->offset = _passedBufferState[_amountSubmitted++].offset;
                    _instancedDataBuffer++;
                }
            }
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
        _vertexDataBuffer = (reach::ParticleVertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    }

    void reach::ParticleSystem::_setBuffer(ParticleVertexData& buffer){
        _vertexDataBuffer->position = buffer.position;
        _vertexDataBuffer->color = buffer.color;
        _vertexDataBuffer++;
           
    }

    void ParticleSystem::submit(entt::basic_registry<entt::entity>* registry){
        //submit particle systems as a component to render different batches
        //auto renderables = registry->view<TransformComponent, RenderableComponent, ParticleEmitterComponent>();
        auto group = registry->group<TransformComponent, RenderableComponent, ParticleEmitterComponent>();
        
        for(auto entity: group) {
            reach::TransformComponent &transform = group.get<TransformComponent>(entity);
            reach::RenderableComponent &renderable = group.get<RenderableComponent>(entity);
            reach::ParticleEmitterComponent &emitter = group.get<ParticleEmitterComponent>(entity);
            
            ParticleVertexData data;
            data.position = transform.position;
            data.color = glm::vec4(Random::GenerateFloat(),Random::GenerateFloat(),Random::GenerateFloat(),1.0f);
            _setBuffer(data);
            
            data.position = transform.position + glm::vec2(transform.scale.x, 0);
            data.color = glm::vec4(Random::GenerateFloat(),Random::GenerateFloat(),Random::GenerateFloat(),1.0f);
            _setBuffer(data);

            data.position = transform.position + glm::vec2(0, transform.scale.y);
            data.color = glm::vec4(Random::GenerateFloat(),Random::GenerateFloat(),Random::GenerateFloat(),1.0f);
            _setBuffer(data);

            data.position = transform.position + glm::vec2(transform.scale.x, transform.scale.y);
            data.color = glm::vec4(Random::GenerateFloat(),Random::GenerateFloat(),Random::GenerateFloat(),1.0f);
            _setBuffer(data);

            data.position = transform.position + glm::vec2(0, transform.scale.y);
            data.color = glm::vec4(Random::GenerateFloat(),Random::GenerateFloat(),Random::GenerateFloat(),1.0f);
            _setBuffer(data);

            data.position = transform.position + glm::vec2(transform.scale.x, 0);
            data.color = glm::vec4(Random::GenerateFloat(),Random::GenerateFloat(),Random::GenerateFloat(),1.0f);

            _setBuffer(data);

            
        }

    }

    void ParticleSystem::end(){
        //unbind dynamic buffer
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }


    void ParticleSystem::flush(){

        glBindVertexArray(_vertexArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 1000); 
        //glDrawElementsInstanced(GL_TRIANGLES, 60, GL_UNSIGNED_BYTE, (const void*)0, 100); 
        glBindVertexArray(0);

    }


}