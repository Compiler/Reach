#include "ReachCore.h"

namespace reach{


    void ReachCore::load(){
        StartupSystems::_initGLFW();
       _windowRef = new reach::Window(1920, 1080, "Reach", false);
        StartupSystems::_initGlad();


        
        auto registry = entt::registry();
        auto entity = registry.create();
        registry.emplace<TransformComponent>(entity, TransformComponent());
        auto pos = registry.get<TransformComponent>(entity);
        REACH_LOG("Pos: (" << pos.position.x << ", "<< pos.position.y << ", "<< pos.position.z << ")");
        pos.position.x = 4;
        REACH_LOG("Pos: (" << pos.position.x << ", "<< pos.position.y << ", "<< pos.position.z << ")");

    }
    void ReachCore::update(){
        
            
    }
    void ReachCore::render(){

            
    }
    void ReachCore::unload(){

            
    }



}