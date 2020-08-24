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

            float quadVertices[] = {
                // positions     // colors
                -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,1, //0
                0.05f, -0.05f,  0.0f, 1.0f, 0.0f,1,  //1
                -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,1, //2

                -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,1, //0
                0.05f, -0.05f,  0.0f, 1.0f, 0.0f,1,  //1
                0.05f,  0.05f,  0.0f, 1.0f, 1.0f,1	 //5	    		
            };  
            
            glGenBuffers(1, &_instancedBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, _instancedBufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glGenBuffers(1, &_bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
            
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

    }

    void ParticleSystem::begin(){
        //setup dynamic buffer - profile speed gap

    }

    void ParticleSystem::submit(){
        //submit particle systems as a component to render different batches


    }

    void ParticleSystem::end(){
        //unbind dynamic buffer


    }


    void ParticleSystem::flush(){

        glBindVertexArray(_vertexArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); 
        //glDrawElementsInstanced(GL_TRIANGLES, 60, GL_UNSIGNED_BYTE, (const void*)0, 100); 
        glBindVertexArray(0);

    }


}