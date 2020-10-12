#pragma once
#include <math.h>
#include <iostream>

namespace reach{

    constexpr float roundInterval(float number, float interval){
        float n = number / interval;
        float whole = floor(n );
        float decimal = n - whole;
        float returnedValue = interval * whole;
        if(decimal >= 0.5) returnedValue += interval;
        return returnedValue;
        
    }

    constexpr float lerp(float a, float b, float t) {
        if(a<=0 && b>=0 || a>=0 && b<=0) return t*b + (1-t)*a;
        if(t==1) return b;
        const float x = a + t*(b-a);
        return t>1 == b>a ?( b > x ? b : x) : ( b < x ? b : x);  
    }

    constexpr glm::vec2 lerp(glm::vec2 a, glm::vec2 b, glm::vec2 t) {
        return glm::vec2(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y));
    }
    constexpr glm::vec3 lerp(glm::vec3 a, glm::vec3 b, glm::vec3 t) {
        return glm::vec3(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y), lerp(a.z, b.z, t.z));
    }
    constexpr glm::vec4 lerp(glm::vec4 a, glm::vec4 b, glm::vec4 t) {
        return glm::vec4(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y), lerp(a.z, b.z, t.z), lerp(a.w, b.w, t.w));
    }
} 