#include <Reach/ReachCore.h>
#include <Reach/Tools/Logging/Logger.h>
#include <iostream>
int main(){

    REACH_LOG("Initializing Gerl...");
    reach::ReachCore core;
    core.load();
    REACH_LOG("Beginning Render loop");
    while(core.isRunning()){
        core.update();
        core.render();
    }
    REACH_LOG("Unloading Gerl...");
    core.unload();

    REACH_MAGENTA("Gerl Closed.");
    return 0;

}