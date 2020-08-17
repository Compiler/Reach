#include "ReachCore.h"

namespace reach{


    void ReachCore::load(){
        StartupSystems::_initGLFW();
       	_windowRef = new reach::Window(1920, 1080, "Reach", false);
        StartupSystems::_initGlad();
		glfwSetWindowUserPointer(_windowRef->getWindow(), this);
		glfwSetKeyCallback(_windowRef->getWindow(), GLFWCallbacks::keyCallback);
		glfwSetCursorPosCallback(_windowRef->getWindow(), GLFWCallbacks::cursorPositionCallback);
		glfwSetMouseButtonCallback(_windowRef->getWindow(), GLFWCallbacks::mouseClickCallback);
		glfwSwapInterval(0);


		DebugScene* a = _sceneManager.emplaceScene<DebugScene>();
		a->setName("scene 1");
		a->_set_color_(0,0,1,1);
		auto b = _sceneManager.emplaceScene<DebugScene>();
		b->_set_color_(0,1,0,1);
		b->addEntity(-0.5, 0, 1, 0, 0);
		_sceneManager.setCurrentScene(b);
    }
    void ReachCore::update(){
		msPerFrame = (glfwGetTime() * 1000.0f) - previousMSPerFrame;
		previousMSPerFrame = glfwGetTime() * 1000.0f;
		accumMSFPS += msPerFrame;
		if(accumMSFPS >= 1000){
			static std::string title;
			_windowRef->setTitle(std::string("Reach - fps " + std::to_string((int)framesPerSecond) + " - ms " + std::to_string(msPerFrame)).c_str());
			framesPerSecond = 0;
			accumMSFPS = 0;
		}
        glfwPollEvents();
		_sceneManager.update();

		if(InputManager::isKeyPressed(reach::KeyCodes::KEY_A)) REACH_WARN("A");
		if(glfwWindowShouldClose(_windowRef->getWindow())) _running = 0;
		InputManager::clear();
    }
    void ReachCore::render(){
		_sceneManager.render();
        glfwSwapBuffers(_windowRef->getWindow());
        
		framesPerSecond ++;
    }
    void ReachCore::unload(){

            
    }



}