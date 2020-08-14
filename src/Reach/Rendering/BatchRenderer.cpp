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
        _dataBuffer->position  =    data.position;
        _dataBuffer->color     =    data.color;
        _dataBuffer->texCoords =    data.texCoords;
        _dataBuffer++;
           
    }

    void BatchRenderer::submit(entt::basic_registry<entt::entity>& registry){
        //todo check if registry is global or local and get components with renderable component   
        entt::basic_view<entt::entity, entt::exclude_t<>, reach::TransformComponent, reach::RenderableComponent> renderables = registry.view<TransformComponent, RenderableComponent>(); 
    }

    void BatchRenderer::end(){


    }

    void BatchRenderer::flush(){


    }



}