#include "ParticleSystem.h"

namespace reach{


    void ParticleSystem::init(TextureComponent particle){

            REACH_LOG("BatchRenderer initializing...");
            glGenVertexArrays(1, &_vertexArrayID);
            glBindVertexArray(_vertexArrayID);

            float quadVertices[] = {
                // positions     // colors
                -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,1,
                0.05f, -0.05f,  0.0f, 1.0f, 0.0f,1,
                -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,1,

                -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,1,
                0.05f, -0.05f,  0.0f, 1.0f, 0.0f,1,
                0.05f,  0.05f,  0.0f, 1.0f, 1.0f,1		    		
            };  

            glGenBuffers(1, &_bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
            
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

           // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, REACH_VERTEXDATA_SIZE, (const void*)  0                  ); // POSITION
           // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, REACH_VERTEXDATA_SIZE, (const void*) (2 * sizeof(float)) ); // COLOUR
           // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, REACH_VERTEXDATA_SIZE, (const void*) (6 * sizeof(float)) ); // TEXTURE COORDINATES
           // 
           // 
           // glGenBuffers(1, &_indexBufferID);
           // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
           // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_ind), _ind, GL_STATIC_DRAW);
           // glBindVertexArray(0);


    }



}