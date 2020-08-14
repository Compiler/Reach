#include "ReachCore.h"

namespace reach{


    void ReachCore::load(){
        StartupSystems::_initGLFW();
       _windowRef = new reach::Window(1920, 1080, "Reach", false);
        StartupSystems::_initGlad();
        
    }
    void ReachCore::update(){
        
            
    }
    void ReachCore::render(){

            
    }
    void ReachCore::unload(){

            
    }



}