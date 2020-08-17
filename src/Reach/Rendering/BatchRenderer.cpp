#include "BatchRenderer.h"

namespace reach{

    void BatchRenderer::init(){

            REACH_LOG("BatchRenderer initializing...");
            glGenVertexArrays(1, &_vertexArrayID);
            glBindVertexArray(_vertexArrayID);

            glGenBuffers(1, &_bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * REACH_MAX_RENDERABLE, NULL, GL_DYNAMIC_DRAW);
            
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, REACH_VERTEXDATA_SIZE, (const void*)  0                  ); // POSITION
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, REACH_VERTEXDATA_SIZE, (const void*) (2 * sizeof(float)) ); // COLOUR
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, REACH_VERTEXDATA_SIZE, (const void*) (6 * sizeof(float)) ); // TEXTURE COORDINATES
            
            
            glGenBuffers(1, &_indexBufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
            uint32_t offset = 0;
            for(int i = 0; i < REACH_INDEX_BUFFER_SIZE; i+= 6){
                _ind[i + 0] = offset + 0;
                _ind[i + 1] = offset + 1;
                _ind[i + 2] = offset + 2;
                _ind[i + 3] = offset + 3;
                _ind[i + 4] = offset + 1;
                _ind[i + 5] = offset + 2;
                offset+=4;
            }
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_ind), _ind, GL_STATIC_DRAW);

            glBindVertexArray(0);
            //assert(FAR_BUFFER_SIZE % 8 == 0);
            _amountSubmitted = 0;

    }

    void BatchRenderer::begin(){
        glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
        _dataBuffer = (reach::VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    }

    void reach::BatchRenderer::_setBuffer(VertexData data){
        //  REACH_DEBUG("Submitted:\n\tPosition: (" << data.position.x << ", "<< data.position.y << ")\n\tColor: ("
        //  << data.color.x << ", "<< data.color.y << ", "<< data.color.z << ", "<< data.color.w<< ")\n\tTexCoords: ("<< data.texCoords.x << ", "<< data.texCoords.y << ")");
        _dataBuffer->position  =    data.position;
        _dataBuffer->color     =    data.color;
        _dataBuffer->texCoords =    data.texCoords;
        _dataBuffer++;
           
    }

    void BatchRenderer::submit(entt::basic_registry<entt::entity>* registry){
        //todo check if registry is global or local and get components with renderable component   
        auto renderables = registry->view<TransformComponent, RenderableComponent, TextureComponent>();
        for(auto entity: renderables) {
            reach::TransformComponent &transform = renderables.get<TransformComponent>(entity);
            reach::RenderableComponent &renderable = renderables.get<RenderableComponent>(entity);
            reach::TextureComponent &texture = renderables.get<TextureComponent>(entity);
            static glm::vec2 initScale = glm::vec2(1,1);

            VertexData t1, t2, t3, t4;
            t1.position = transform.position;
            t1.color = renderable.color;
            t1.texCoords = glm::vec3(0, 0, 1);

            t2.position = transform.position;
            t2.position.x += (initScale.x * transform.scale.x);
            t2.color = renderable.color;
            t2.texCoords = glm::vec3(1, 0, 1);

            t3.position = transform.position;
            t3.position.y += (initScale.y * transform.scale.y);
            t3.color = renderable.color;
            t3.texCoords = glm::vec3(0, 1, 1);
            
            t4.position = transform.position;
            t4.position.x += (initScale.x * transform.scale.x);
            t4.position.y += (initScale.y * transform.scale.y);
            t4.color = renderable.color;
            t4.texCoords = glm::vec3(1, 1, 1);

            _setBuffer(t1);_setBuffer(t2);_setBuffer(t3);
            _setBuffer(t4);_setBuffer(t2);_setBuffer(t3);

            _amountSubmitted+=6;
            glBindTextureUnit(GL_TEXTURE0 + 1, texture.id);
        }
    }

    void BatchRenderer::end(){

        glUnmapBuffer(GL_ARRAY_BUFFER);

    }

    void BatchRenderer::flush(){
        static bool flag = 1;
        if(flag){
            REACH_WARN(_amountSubmitted << " entities submitted");
            flag = 0;
        }
        glBindVertexArray(_vertexArrayID);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
        glDrawElements(GL_TRIANGLES, _amountSubmitted, GL_UNSIGNED_SHORT, 0);
        _amountSubmitted = 0;

    }



}