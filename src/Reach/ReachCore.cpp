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


		_sceneManager.emplaceScene<DebugScene>()->setName("scene 1");
		_sceneManager.emplaceScene<DebugScene>()->setName("scene 2");
    }
    void ReachCore::update(){
        glfwPollEvents();
		_sceneManager.update();

		if(InputManager::isKeyPressed(reach::KeyCodes::KEY_A)) REACH_WARN("A");
		if(glfwWindowShouldClose(_windowRef->getWindow())) _running = 0;
		InputManager::clear();
    }
    void ReachCore::render(){
		_sceneManager.render();
        glfwSwapBuffers(_windowRef->getWindow());
            
    }
    void ReachCore::unload(){

            
    }



}