#include "SystemManager.h"


namespace reach{

    void SystemManager::addSystem(reach::System* system){
        _systems.push_back(system);

    }

    void SystemManager::update(entt::basic_registry<entt::entity>* registry){
        for(int i = 0; i < _systems.size(); i++) _systems[i]->update(registry);
    }

}