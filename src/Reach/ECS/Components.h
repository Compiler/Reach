#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
namespace reach{


    uint64_t hash_name(const char* str);

    struct NameComponent{

        const char* name;

    };

    struct TransformComponent{

        glm::vec2 position;
        glm::vec2 rotation;
        glm::vec2 scale;

        TransformComponent(){}
        TransformComponent(float x, float y): position(glm::vec2(x,y)){}

    };

    struct RenderableComponent{

        glm::vec4 color;

    };
    struct TextureComponent{

        uint32_t id = -1;
        uint64_t keyFileName = -1;
        uint32_t bitsPerPixel = 0;
        const char* fileName;

    };

    struct RenderableParticle{
        float lifeTime = 1.0f;
        float timeAlive;
        bool active = true;
        glm::vec2 position;//todo: xy = position, zw = last position
        glm::vec4 color;

    };
    struct ParticleEmitterComponent{
        //how many particles to emit :D
        uint16_t emissionCount;
        //the value at which we divide the amount of lifetime decays 
        float decayMagnitude = 1000.0f;
        //what value to go between to multiple the magnitude by
        float decayVariance = 0.0f;

        //how much to multiply a random value between -spawnVariance and spawnVariance against spawnOffset
        float spawnVariance = 1.0f;
        //the amount of pixels to offset the particle 
        glm::vec2 spawnOffset = glm::vec2(0,0);
       
        bool cycle = false;

        std::vector<RenderableParticle> particles;
        std::vector<glm::vec2> velocities;
        std::vector<glm::vec4> colors;


        void addColorWeight(glm::vec4 color, uint16_t weight){
            for(int i = 0; i < weight; i++) colors.push_back(color);
        }
        void addVelocityWeight(glm::vec2 velocity, uint16_t weight){
            for(int i = 0; i < weight; i++) velocities.push_back(velocity);
        }

    };

    struct MovementComponent{
        std::vector<uint16_t> keys;
        std::vector<glm::vec2> velocities;

        void set(uint16_t key, glm::vec2 vel){keys.push_back(key);velocities.push_back(vel);}

    };
}