#include <Reach/ReachCore.h>
#include <Reach/Tools/Logging/Logger.h>
#include <iostream>
#include <entt/entity/registry.hpp>
#define ENTT_STANDALONE
int main(){

    auto registry = entt::registry();
    auto entity = registry.create();


    REACH_LOG("Initializing Gerl...");
    reach::ReachCore core;
    core.load();
    REACH_LOG("Beginning Render loop");
    while(true){
        core.update();
        core.render();
    }
    REACH_LOG("Unloading Gerl...");
    core.unload();

    REACH_MAGENTA("Gerl Closed.");
    return 0;

}