#pragma once



namespace reach{


    class Scene{


        public:

            virtual void load() = 0;
            virtual void update() = 0;
            virtual void render() = 0;
            virtual void unload() = 0;

    };


}