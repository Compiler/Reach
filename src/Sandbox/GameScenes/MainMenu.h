#pragma once
#include <Reach/Tools/Scenes/Scene.h>

namespace sandbox{

    class MainMenu : public reach::Scene{

        explicit MainMenu(const char* name);

        void load()override;
        void update()override;
        void render()override;
        void unload()override;


    };

}