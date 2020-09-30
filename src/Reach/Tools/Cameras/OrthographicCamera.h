#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace reach{


    class OrthographicCamera{

        private:
            float _zoom = 1.0f;
            glm::vec2 _dimensions = glm::vec2(1920, 1080);//defaults
            glm::vec2 _position = glm::vec2(0);
            glm::mat4 _camera;

            float _left, _right;
            float _top, _bottom;
            float _nearClip = 0.1f;
            float _farClip = 1000.0f;

            bool _cameraDirty = true;
            void _setBounds();
            void _init();


        public:
            explicit OrthographicCamera();
            explicit OrthographicCamera(glm::vec2& position, float width, float height);
            explicit OrthographicCamera(float xPos, float yPos, float width, float height);

            void update();


            inline glm::mat4 getCamera(){return _camera;}


    };

}