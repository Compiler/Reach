#pragma once
#include <Tools/Scenes/Scene.h>


namespace reach{


    class SceneManager{


        private:
            Scene* _currentScene;

        public:


            void render();
            void update();

            


    };


}