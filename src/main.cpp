#include <Reach/ReachCore.h>
#include <Reach/Tools/Logging/Logger.h>
#include <iostream>
int main(){

    REACH_BGREEN("Initializing Reach...");
    reach::ReachCore core;
    core.load();
    REACH_BGREEN("Beginning Render loop");
    while(core.isRunning()){
        core.update();
        core.render();
    }
    REACH_BGREEN("Unloading Reach...");
    core.unload();

    REACH_BGREEN("Reach Closed.");
    return 0;

}