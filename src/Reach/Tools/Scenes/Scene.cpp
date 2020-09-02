#include "Scene.h"
#include <string>
namespace reach{
    uint8_t Scene::_COUNT = 0;

	Scene::Scene() :m_sceneName((std::string("Scene") + std::to_string(_COUNT++)).c_str()) {
		m_renderer = new reach::BatchRenderer();
		m_systemManager = new reach::SystemManager();
		m_renderer->init();
        m_registry = entt::registry();
		//m_registry.group<>();
	}
	Scene::Scene(const char* name) : m_sceneName(name) {
		_COUNT++;
		m_renderer = new reach::BatchRenderer();
		m_systemManager = new reach::SystemManager();
		m_renderer->init();
       	m_registry = entt::registry();
		//m_registry.group<>();
	}


	void Scene::load() {
			REACH_LOG("Scene Loaded");
	}
	void Scene::update(float deltaTime){
	}
	void Scene::render(){
	}
	void Scene::unload(){
	}
}