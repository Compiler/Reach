#include "ParticleRenderer.h"

namespace reach{


    void ParticleRenderer::init(){
            REACH_LOG("ParticleRenderer initializing...");

            _instancesCreated = 0;
            glGenVertexArrays(1, &_vertexArrayID);
            glBindVertexArray(_vertexArrayID);
          

            glGenBuffers(1, &_instancedBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, _instancedBufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleInstancedData) * REACH_MAX_RENDERABLE, NULL, GL_DYNAMIC_DRAW);
            //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            int _c_ = 0;
            REACH_DEBUG(_c_++);


            glGenBuffers(1, &_bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleVertexData) * REACH_MAX_RENDERABLE, NULL, GL_DYNAMIC_DRAW);
            
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertexData), (const void*)  0); // POSITION


            glBindBuffer(GL_ARRAY_BUFFER, _instancedBufferID);

            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleInstancedData), (const void*) (2 * sizeof(float)) ); // COLOUR
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleInstancedData), (const void*) (0 * sizeof(float)) );
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            glVertexAttribDivisor(1, 1);
            glVertexAttribDivisor(2, 1); 

            glBindVertexArray(0);

            REACH_DEBUG("Finished initialization of ParticleRenderer");
    }

    void ParticleRenderer::begin(){
        //setup dynamic buffer - profile speed gap
        glBindBuffer(GL_ARRAY_BUFFER, _instancedBufferID);
        _instancedDataBuffer = (reach::ParticleInstancedData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        _amountSubmitted = 0;
        _instancesCreated = 0;

    }

    void reach::ParticleRenderer::_setBuffer(ParticleVertexData& buffer){
        _vertexDataBuffer->position = buffer.position;
        //_vertexDataBuffer->color = buffer.color;
        _vertexDataBuffer++;
           
    }

    void ParticleRenderer::submit(entt::basic_registry<entt::entity>* registry){
        //submit particle systems as a component to render different batches
        auto group = registry->group<TransformComponent, RenderableComponent, ParticleEmitterComponent>();
        for(auto entity: group) {
            reach::TransformComponent &transform = group.get<TransformComponent>(entity);
            reach::RenderableComponent &renderable = group.get<RenderableComponent>(entity);
            reach::ParticleEmitterComponent &emitter = group.get<ParticleEmitterComponent>(entity);
            for(int i = 0; i < emitter.emissionCount; i++){
                _instancedDataBuffer->offset = emitter.particles[i].position;
                _instancedDataBuffer->color = emitter.particles[i].color;
                _instancesCreated += emitter.particles[i].active;
                _instancedDataBuffer += emitter.particles[i].active; 
            }


            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
            _vertexDataBuffer = (reach::ParticleVertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            ParticleVertexData data;
            data.position = transform.position;
            _setBuffer(data);
            
            data.position = transform.position + glm::vec2(transform.scale.x, 0);
            _setBuffer(data);

            data.position = transform.position + glm::vec2(0, transform.scale.y);
            _setBuffer(data);

            data.position = transform.position + glm::vec2(transform.scale.x, transform.scale.y);
            _setBuffer(data);

            data.position = transform.position + glm::vec2(transform.scale.x, 0);
            _setBuffer(data);

            data.position = transform.position + glm::vec2(0, transform.scale.y);
            _setBuffer(data);

            
        }

    }

    void ParticleRenderer::end(){
        //unbind dynamic buffer
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }


    void ParticleRenderer::flush(){

        glBindVertexArray(_vertexArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, _instancesCreated); 
        //glDrawElementsInstanced(GL_TRIANGLES, 60, GL_UNSIGNED_BYTE, (const void*)0, 100); 
        glBindVertexArray(0);

    }


}