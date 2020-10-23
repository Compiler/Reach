#pragma once
#include <random>

namespace reach{

    class Random{

        public:
            static void init(){
                _RANDOM_ENGINE.seed(std::random_device()());
            }

            /** 
                * Generates a float using Mersenne Twister Random Number Generator Algorithm
                * @return the random value
            */
            static float GenerateFloat(){
                return(float)_DISTRIBUTION(_RANDOM_ENGINE) / (float)std::numeric_limits<uint32_t>::max();
            }    

            /** 
                * Seeds the Mersenne Twister Random Number Generator Algorithm
                * @param seed the seed
            */
            static void seed(int seed){
                _RANDOM_ENGINE.seed(seed);
            }

            /** 
                * Generates an unsigned 32bit integer using Lehmer Random Number Generator Algorithm
                * @return the random value
            */
            static uint32_t GenerateLehmer32(){
                nLehmer += 0xe120fc15;
                uint64_t tmp;
                tmp = (uint64_t)nLehmer * 0x4a39b70d;
                uint32_t m1 = (tmp >> 32) ^ tmp;
                tmp = (uint64_t)m1* 0x12fad5c9;
                uint32_t m2 = (tmp >> 32) ^ tmp;
                return m2;

            }
            static uint32_t nLehmer;
        private:

            static std::mt19937 _RANDOM_ENGINE;
            static std::uniform_int_distribution<std::mt19937::result_type> _DISTRIBUTION;


    };


}