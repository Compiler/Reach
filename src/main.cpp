#include <Reach/ReachCore.h>
#include <iostream>
int main(){

   // REACH_LOG("Hello");
    std::cout <<"Beginning\n";
    reach::ReachCore core;
    core.load();

    while(true){
        core.update();
        core.render();
    }
    core.unload();
    return 0;

}