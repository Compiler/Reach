#include "Box2DDebugRenderer.h"

 namespace reach{

     Box2DDebugRenderer::Box2DDebugRenderer(){
        glGenVertexArrays(1, &_vertexID);
        glBindVertexArray(_vertexID);

        float x=  0.25;
        float verts[6] = {
            -x, -x,     x, -x,  -x,x
        };

        glGenBuffers(1, &_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
            
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2), (const void*)  0); // POSITION
        
        _debugShader.loadShader(REACH_INTERNAL_SHADER("b2dDebug.vert"), REACH_INTERNAL_SHADER("b2dDebug.frag"));
     }


	void Box2DDebugRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
            _debugShader.use();
            float x=  0.25;
            float verts[6] = {-x, -x,     x, -x,  -x,x};

            glBindVertexArray(_vertexID);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    //        glBufferData(GL_ARRAY_BUFFER, vertexCount, vertices, GL_STATIC_DRAW);
            //for(int i = 0; i < vertexCount; i++)REACH_DEBUG((vertices+i)->x << ", " << (vertices+i)->y);
            //REACH_ERROR("");
            glDrawArrays(GL_TRIANGLES, 0, 6);
           // REACH_LOG("Drawing polygon");
    }

	void Box2DDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
            //_debugShader.use();
           // glBindVertexArray(_vertexID);
            //glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
            //glBufferData(GL_ARRAY_BUFFER, vertexCount, vertices, GL_STATIC_DRAW);
            //glDrawArrays(GL_LINE, 0, vertexCount);
           //REACH_LOG("Drawing Solid polygon");

    }

	void Box2DDebugRenderer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color){


    }

	void Box2DDebugRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color){

    }

	void Box2DDebugRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){

    }

	void Box2DDebugRenderer::DrawTransform(const b2Transform& xf){


    }

	void Box2DDebugRenderer::DrawPoint(const b2Vec2& p, float size, const b2Color& color){


    }


 }