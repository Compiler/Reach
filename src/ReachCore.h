#pragma once

namespace reach{


    class ReachCore{


        public:

            void load();
            void update();
            void render();
            void unload();
            bool isRunning() { return 1;}

    };

}