#pragma once
#include <random>

namespace reach{

    class Random{

        public:
            static void init(){
                _RANDOM_ENGINE.seed(std::random_device()());
            }

            static float GenerateFloat(){
                return(float)_DISTRIBUTION(_RANDOM_ENGINE) / (float)std::numeric_limits<uint32_t>::max();
            }    
        private:

            static std::mt19937 _RANDOM_ENGINE;
            static std::uniform_int_distribution<std::mt19937::result_type> _DISTRIBUTION;


    };


}