#include "ReachCore.h"

namespace reach{

    void ReachCore::loadShaders(const char* vertexFile, const char* fragmentFile){
	unsigned int vertexShader, fragmentShader;
	std::string vertSrc, fragSrc;
	reach::FileLoaderFactory::loadTextFromFile(vertexFile, vertSrc);
	reach::FileLoaderFactory::loadTextFromFile(fragmentFile, fragSrc);
	const char* vert = vertSrc.c_str();
	const char* frag = fragSrc.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vert, NULL);
	glCompileShader(vertexShader);
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if(!success){
    		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\t %s", infoLog );
		}
	}
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &frag, NULL);
	glCompileShader(fragmentShader);

	{
		int  success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if(!success){
    		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    		printf("ERROR::SHADER::FRAG::COMPILATION_FAILED\t %s", infoLog );
		}
	}

	_shaderProgram = glCreateProgram();

	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	{
		int  success;
		char infoLog[512];
		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
		if(!success) {
    		glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
    		printf("ERROR::SHADER::COMP::COMPILATION_FAILED\t %s", infoLog );
		}
	}

}

    void ReachCore::load(){
        StartupSystems::_initGLFW();
       _windowRef = new reach::Window(1920, 1080, "Reach", false);
        StartupSystems::_initGlad();
		glfwSetWindowUserPointer(_windowRef->getWindow(), this);
		glfwSetKeyCallback(_windowRef->getWindow(), GLFWCallbacks::keyCallback);
		glfwSetCursorPosCallback(_windowRef->getWindow(), GLFWCallbacks::cursorPositionCallback);
		glfwSetMouseButtonCallback(_windowRef->getWindow(), GLFWCallbacks::mouseClickCallback);

        _renderer = new BatchRenderer();
        _renderer->init();


        
        _registry = entt::registry();
    	auto e = _registry.create();
        auto &pos = _registry.emplace<TransformComponent>(e, TransformComponent());
		pos.position = glm::vec2(-0.5f, -0.5f);
		pos.scale = glm::vec2(1, 1);
        REACH_LOG("Pos: (" << pos.position.x << ", "<< pos.position.y << ")");
        pos.position.x = -0.25;
        pos.scale = glm::vec2(1,1);
        REACH_LOG("Pos: (" << pos.position.x << ", "<< pos.position.y << ")");

        auto &rend = _registry.emplace<RenderableComponent>(e, RenderableComponent());
		rend.color = glm::vec4(1,0,1,1);
        loadShaders(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));

    }
    void ReachCore::update(){
        glfwPollEvents();


		if(glfwWindowShouldClose(_windowRef->getWindow())) _running = 0;
		InputManager::clear();

    }
    void ReachCore::render(){

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glClearColor(0.2, 0.2, 0.4, 1.0);


        glUseProgram(_shaderProgram);
        _renderer->begin();
        _renderer->submit(&_registry);
        _renderer->end();
        _renderer->flush();


        glfwSwapBuffers(_windowRef->getWindow());
            
    }
    void ReachCore::unload(){

            
    }



}