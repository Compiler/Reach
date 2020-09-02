#include "ReachCore.h"

namespace reach{


    void ReachCore::load(){
        StartupSystems::_initGLFW();
       	_windowRef = new reach::Window(1920, 1080, "Reach", false);
        StartupSystems::_initGlad();
		StartupSystems::_initTextureManager();
		glfwSetWindowUserPointer(_windowRef->getWindow(), this);
		glfwSetKeyCallback(_windowRef->getWindow(), GLFWCallbacks::keyCallback);
		glfwSetCursorPosCallback(_windowRef->getWindow(), GLFWCallbacks::cursorPositionCallback);
		glfwSetMouseButtonCallback(_windowRef->getWindow(), GLFWCallbacks::mouseClickCallback);
		glfwSwapInterval(0);
		// glEnable(GL_CULL_FACE);
		// glCullFace(GL_BACK);
		// glFrontFace(GL_CW);

		//DebugScene* a = _sceneManager.emplaceScene<DebugScene>();
		//a->setName("scene 1");
		//a->_set_color_(0,0,1,1);
		auto b = _sceneManager.emplaceScene<DebugScene>();
		b->_set_color_(0.2,0,0.2,1);
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
		_sceneManager.update(msPerFrame);

		if(glfwWindowShouldClose(_windowRef->getWindow())) _running = 0;
    }
    void ReachCore::render(){
		_sceneManager.render();
        glfwSwapBuffers(_windowRef->getWindow());
        
		InputManager::clear();
		framesPerSecond ++;
    }
    void ReachCore::unload(){

            
    }



}