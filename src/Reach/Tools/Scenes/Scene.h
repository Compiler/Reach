#pragma once
#include <Reach/Tools/Logging/Logger.h>
#include <stdint.h>

namespace reach{


    class Scene{


        private:
		static uint8_t _COUNT;
		const char* _sceneName;

        protected:

        public:
            Scene();
            Scene(const char* name);


            virtual void load();
            virtual void update();
            virtual void render();
            virtual void unload();

            inline const char* getName()const { return _sceneName; }

    };


}