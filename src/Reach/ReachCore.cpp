#include "ReachCore.h"

namespace reach{

	float DELTA_TIME = 0.0f;
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
			framesPerSecond = 0;
			accumMSFPS = 0;
		}
		reach::DELTA_TIME = msPerFrame;
        glfwPollEvents();
		_sceneManager.update();

    }
    void ReachCore::render(){
		// ImGui_ImplOpenGL3_NewFrame();
		// ImGui_ImplGlfw_NewFrame();
		// ImGui::NewFrame();

		
		// bool open = true;
		// ImGui::ShowDemoWindow(&open);
		// if(ImGui::BeginMainMenuBar()){
		// 	if(ImGui::BeginMenu("File")){
		// 		ImGui::EndMenu();
		// 	}
		// 	ImGui::EndMainMenuBar();
		// }

		// ImGui::Begin("Demo window");
    	// ImGui::Button("Hello!");
    	// ImGui::End();

		// ImGui::Render();
		// ImGui::EndFrame();
		_sceneManager.render();


        glfwSwapBuffers(_windowRef->getWindow());
        
		InputManager::clear();
		framesPerSecond ++;
    }
    void ReachCore::unload(){

            
    }



}