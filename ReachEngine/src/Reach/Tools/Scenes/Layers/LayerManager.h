#pragma once
#include <Reach/Tools/Scenes/Layers/Layer.h>
#include <vector>
#include <stdio.h>
#include <stdint.h>

namespace reach{


    class LayerManager {
	private:
		std::vector<reach::Layer*> _layers;
		uint8_t _currentLayer = 0;
		uint8_t _nextLayer = 0;

		bool _dirty = true;

		glm::vec4 _clearColor;
	public:

		LayerManager() = default;

		void update();
		void render();


		Layer* getLayerByName(const char* name) {
			for (int i = 0; i < _layers.size(); i++) {
				if (name == _layers[i]->getName()) return _layers[i];
			}
		}

		void setCurrentLayer(Layer scene);
		void setCurrentLayer(const Layer& scene);
		void setCurrentLayer(Layer* scene);
		void setCurrentLayer(const char* name);
		void setCurrentLayer(uint8_t sceneIndex);

		void addLayer(Layer&& scene);
		void addLayer(Layer* scene);
		void addLayerRef(const Layer& scene);
		void addLayer(Layer scene);

		void setClearColor(glm::vec4);

		template<typename T>
		T* emplaceLayer(){
			T* t = new T();
			_layers.push_back(t);
			return t;
		}
		
		inline Layer& getCurrentLayer() { return *_layers[_currentLayer]; }
		inline uint8_t getCurrentLayerIndex()const { return _currentLayer; }
	};


}