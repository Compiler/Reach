#include "Scene.h"
#include <string>
namespace reach{
    uint8_t Scene::_COUNT = 0;

	Scene::Scene() :_sceneName((std::string("Scene") + std::to_string(_COUNT++)).c_str()) {}
	Scene::Scene(const char* name) : _sceneName(name) { _COUNT++; }


	void Scene::load() {
	}
	void Scene::update(){
	}
	void Scene::render(){
	}
	void Scene::unload(){
	}
}