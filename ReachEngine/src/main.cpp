#include <Reach/ReachCore.h>
#include <Reach/Reach.h>
#include <Reach/Tools/Logging/Logger.h>
#include <iostream>
//picking dedicated gpu
//#include <windows.h>
// extern "C" {
//     _declspec(dllexport) DWORD NvOptimusEnablement = 1;
//     _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
// }

double MAX_FPS=144;
int main(){

    REACH_BGREEN("Initializing Reach...");
    reach::ReachCore core;
    core.load();
    REACH_BGREEN("Beginning Render loop");
    double lastTime = glfwGetTime();
    while(core.isRunning()){
        double time = glfwGetTime();
        double deltaTime = time - lastTime;
        reach::DELTA_TIME = deltaTime;
        if( deltaTime >= 1.0/MAX_FPS ) {
            lastTime = time;
            core.update();
            core.render();
        }
    }
    REACH_BGREEN("Unloading Reach...");
    core.unload();

    REACH_BGREEN("Reach Closed.");
    return 0;

}