#include <Reach/ReachCore.h>
#include <Reach/Tools/Logging/Logger.h>
#include <iostream>
//picking dedicated gpu
//#include <windows.h>
// extern "C" {
//     _declspec(dllexport) DWORD NvOptimusEnablement = 1;
//     _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
// }
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