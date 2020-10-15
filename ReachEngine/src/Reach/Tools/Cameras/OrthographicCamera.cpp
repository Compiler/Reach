#include "OrthographicCamera.h"

namespace reach{


    OrthographicCamera::OrthographicCamera(){
        _setBounds();
        update();
        

    }
    
    OrthographicCamera::OrthographicCamera(glm::vec2& position, float width, float height):_position(position), _dimensions(glm::vec2(width, height)){
        _setBounds();
        update();


    }
    
    OrthographicCamera::OrthographicCamera(float xPos, float yPos, float width, float height): _position(glm::vec2(xPos, yPos)), _dimensions(glm::vec2(width, height)){
        _setBounds();
        update();
    }

    void OrthographicCamera::update(){
        if(_cameraDirty){
            _setBounds();
            _projection = glm::ortho(_left, _right, _bottom, _top, _nearClip, _farClip);
            _view = glm::mat4(1);
            _view = glm::translate(_view, glm::vec3(0.0f, 0.0f, -3.0f)); 
            _combined = _projection * _view;
            _cameraDirty = false;
        }
        

    }

    void OrthographicCamera::translate(glm::vec2 translation){
        _position += translation;
        _cameraDirty = true;
    }


    void OrthographicCamera::setPosition(glm::vec2 position){
        _position = position;
        _cameraDirty = true;
    }
    void OrthographicCamera::_setBounds(){
        _left = _position.x;
        _right= _position.x + _dimensions.x;

        _bottom = _position.y;
        _top = _position.y + _dimensions.y;
    }


}