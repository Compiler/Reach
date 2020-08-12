#include <Reach/ReachCore.h>
#include <iostream>
int main(){


    std::cout <<"Beginning\n";
    reach::ReachCore core;
    core.load();

    while(core.isRunning()){
        core.update();
        core.render();
    }
    core.unload();
    return 0;

}