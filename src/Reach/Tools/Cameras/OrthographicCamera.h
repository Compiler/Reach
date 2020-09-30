#pragma once
#include <glm/glm.hpp>

namespace reach{


    class OrthographicCamera{

        private:
            float _width = 1920, _height = 1080;
            float _zoom = 1.0f;
            glm::vec2 _position = glm::vec2(0);

            float _left, _right;
            float _top, _bottom;

        public:
            explicit OrthographicCamera();


    };

}