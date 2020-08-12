#include "ReachCore.h"

int main(){

    reach::ReachCore core;
    core.load();

    while(core.isRunning()){
        core.update();
        core.render();
    }
    core.unload();
    return 0;

}