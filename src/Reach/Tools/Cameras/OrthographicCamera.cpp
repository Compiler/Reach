#include "OrthographicCamera.h"

namespace reach{


    explicit OrthographicCamera::OrthographicCamera(){
        _setBounds();
        update();
        

    }
    
    explicit OrthographicCamera::OrthographicCamera(glm::vec2& position, float width, float height):_position(position), _dimensions(glm::vec2(width, height)){
        _setBounds();
        update();


    }
    
    explicit OrthographicCamera::OrthographicCamera(float xPos, float yPos, float width, float height): _position(glm::vec2(xPos, yPos)), _dimensions(glm::vec2(width, height)){
        _setBounds();
        update();
    }

    void OrthographicCamera::update(){
        if(_cameraDirty){
            _camera = glm::ortho(_left, _right, _bottom, _top, _nearClip, _farClip);
            _cameraDirty = false;
        }
        

    }

    void OrthographicCamera::_setBounds(){
        _left = _position.x;
        _right= _position.x + _dimensions.x;

        _bottom = _position.y;
        _top = _position.y + _dimensions.y;
    }


}