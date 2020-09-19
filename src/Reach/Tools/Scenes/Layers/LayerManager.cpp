#include "LayerManager.h"

namespace reach{


    void LayerManager::update() {
		//swap scene requested
		if (_nextLayer != _currentLayer) _dirty = true;
		if (_dirty) {
			if(_nextLayer != _currentLayer) _layers[_currentLayer]->unload();
			_dirty = false;
			_currentLayer = _nextLayer;
			_layers[_currentLayer]->load();
		}
		_layers[_currentLayer]->update();
	}
	void LayerManager::render(){
		_layers[_currentLayer]->render();
	}

	void LayerManager::addLayer(Layer* scene) {
		_layers.push_back(scene);
		if (_currentLayer == 255) _currentLayer = 0;
	}

	void LayerManager::setCurrentLayer(Layer scene) {
		const char* nextName = scene.getName();
		for (int i = 0; i < _layers.size(); i++) {
			if (nextName == _layers[i]->getName()) _nextLayer = i;
		}

	}
	void LayerManager::setCurrentLayer(const char* name) {
		for (int i = 0; i < _layers.size(); i++) {
			if (name == _layers[i]->getName()) _nextLayer = i;
		}
	}
	void LayerManager::setCurrentLayer(Layer* scene) {
		auto name = scene->getName();
		for (int i = 0; i < _layers.size(); i++) {
			if (name == _layers[i]->getName()) _nextLayer = i;
		}
	}
	void LayerManager::setCurrentLayer(uint8_t sceneIndex) {
		if (sceneIndex >= 0 && sceneIndex < _layers.size()) _currentLayer = sceneIndex;
	}


}