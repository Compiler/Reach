 #pragma once
 #include <Reach/Reach.h>
 #include <Box2D/box2d.h>
 #include <Box2D/b2_draw.h>
 #include <Box2D/b2_settings.h>
 #include <Reach/Rendering/ShaderProgram.h>
 
 namespace reach{
    class Box2DDebugRenderer : public b2Draw{

        private:
            uint32_t _vertexID, _bufferID;
            ShaderProgram _debugShader;
        public:
            explicit Box2DDebugRenderer();
            void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
            void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
            void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
            void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
            void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
            void DrawTransform(const b2Transform& xf);
            void DrawPoint(const b2Vec2& p, float size, const b2Color& color);
    };
 }