#include "ReachCore.h"

namespace reach{

	float DELTA_TIME = 0.0f;
	float SCREEN_LEFT = 0;
	float SCREEN_RIGHT = 1920;
	float SCREEN_BOTTOM = 0;
	float SCREEN_TOP = 1080;
	int CUR_FPS = 0;
    void ReachCore::load(){
        StartupSystems::_initGLFW();
       	_windowRef = new reach::Window(1920, 1080, "Reach", false);
        StartupSystems::_initGlad();
		StartupSystems::_initTextureManager();
		StartupSystems::_initImGUI(_windowRef->getWindow());
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
		_sceneManager.setCurrentScene(b);
    }
    void ReachCore::update(){
		if(glfwWindowShouldClose(_windowRef->getWindow())) _running = 0;
		msPerFrame = (glfwGetTime() * 1000.0f) - previousMSPerFrame;
		previousMSPerFrame = glfwGetTime() * 1000.0f;
		accumMSFPS += msPerFrame;
		if(accumMSFPS >= 1000){
			static std::string title;
			_windowRef->setTitle(std::string("Reach - fps " + std::to_string((int)framesPerSecond) + " - ms " + std::to_string(msPerFrame)).c_str());
			reach::CUR_FPS = (int)framesPerSecond;
			framesPerSecond = 0;
			accumMSFPS = 0;
		}
        glfwPollEvents();
		_sceneManager.update();

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