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
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, REACH_VERTEXDATA_SIZE, (const void*) (6 * sizeof(float)) ); // TEXTURE COORDINATES
            
            
            glGenBuffers(1, &_indexBufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
            for(int i = 0; i < REACH_INDEX_BUFFER_SIZE; i++) _ind[i] = i;
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_ind), _ind, GL_STATIC_DRAW);

            glBindVertexArray(0);
            //assert(FAR_BUFFER_SIZE % 8 == 0);


    }

    void BatchRenderer::begin(){
        glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
        _dataBuffer = (reach::VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    }

    void reach::BatchRenderer::_setBuffer(VertexData data){
         REACH_DEBUG("Submitted:\n\tPosition: (" << data.position.x << ", "<< data.position.y << ")\n\tColor: ("
         << data.color.x << ", "<< data.color.y << ", "<< data.color.z << ", "<< data.color.w<< ")\n\tTexCoords: ("<< data.texCoords.x << ", "<< data.texCoords.y << ")");
        _dataBuffer->position  =    data.position;
        _dataBuffer->color     =    data.color;
        _dataBuffer->texCoords =    data.texCoords;
        _dataBuffer++;
           
    }

    void BatchRenderer::submit(entt::basic_registry<entt::entity>* registry){
        //todo check if registry is global or local and get components with renderable component   
        auto renderables = registry->view<TransformComponent, RenderableComponent>();
        for(auto entity: renderables) {
            auto &transform = renderables.get<TransformComponent>(entity);
            auto &renderable = renderables.get<RenderableComponent>(entity);
            static glm::vec2 initScale = glm::vec2(1,1);

            VertexData t1, t2, t3;
            t1.position = transform.position;
            t1.color = renderable.color;
            t1.texCoords = glm::vec2(0,0);

            t2.position = transform.position;
            t2.position.x += + (initScale.x * transform.scale.x);
            t2.color = renderable.color;
            t2.texCoords = glm::vec2(0,0);

            t3.position = transform.position;
            t3.position.y += + (initScale.y * transform.scale.y);
            t3.color = renderable.color;
            t3.texCoords = glm::vec2(0,0);

            _setBuffer(t1);_setBuffer(t2);_setBuffer(t3);
            _amountSubmitted+=3;
        }
    }

    void BatchRenderer::end(){

        glUnmapBuffer(GL_ARRAY_BUFFER);

    }

    void BatchRenderer::flush(){
        glBindVertexArray(_vertexArrayID);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
        glDrawElements(GL_TRIANGLES, _amountSubmitted, GL_UNSIGNED_SHORT, 0);
        _amountSubmitted = 0;

    }



}