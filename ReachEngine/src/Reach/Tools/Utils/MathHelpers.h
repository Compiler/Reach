#pragma once
#include <math.h>
#include <iostream>

namespace reach{

/** 
    * Rounds a number up not by nearest whole number but instead by nearest interval. With normal rounding you would round 1.7 to 2 but with
    * interval rounding you would round 3 to the nearest interval. If number = 3.3 and interval = 1.5 then the return value would be 3.  
    * @param [number] the number to be rounded
    * @param [interval] the interval at which to round the number
    * @param [roundNearest] bool to signal how to round the number, if roundNearest = true then if num = 0.6 and interval = 1 then num goes to 1.
    * @return the rounded value
*/
    constexpr float roundInterval(float number, float interval, bool roundNearest=false){
        float n = number / interval;
        float whole = floor(n );
        float decimal = n - whole;
        float returnedValue = interval * whole;
        if(roundNearest) {
            if(decimal >= 0.5) returnedValue += interval;
        }
        return returnedValue;
        
    }
    
    /**
     * Linearly interpolates a float a between a float b by t%
     * @param [a] the number to be linearly interpolated
     * @param [b] the number to hold the max value
     * @param [t] the time( or how far into the interpolation)
     * @return the result of linear interpolation
     */
    constexpr float lerp(float a, float b, float t) {
        if(a<=0 && b>=0 || a>=0 && b<=0) return t*b + (1-t)*a;
        if(t==1) return b;
        const float x = a + t*(b-a);
        return t>1 == b>a ?( b > x ? b : x) : ( b < x ? b : x);  
    }

    /**
     * Linearly interpolates a vec2 a between a vec2 b by t%
     * @param [a] the number to be linearly interpolated
     * @param [b] the number to hold the max value
     * @param [t] the time( or how far into the interpolation)
     * @return the result of linear interpolation
     */
    constexpr glm::vec2 lerp(glm::vec2 a, glm::vec2 b, glm::vec2 t) {
        return glm::vec2(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y));
    }

    /**
     * Linearly interpolates a vec3 a between a vec3 b by t%
     * @param [a] the number to be linearly interpolated
     * @param [b] the number to hold the max value
     * @param [t] the time( or how far into the interpolation)
     * @return the result of linear interpolation
     */
    constexpr glm::vec3 lerp(glm::vec3 a, glm::vec3 b, glm::vec3 t) {
        return glm::vec3(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y), lerp(a.z, b.z, t.z));
    }

    /**
     * Linearly interpolates a vec4 a between a vec4 b by t%
     * @param [a] the number to be linearly interpolated
     * @param [b] the number to hold the max value
     * @param [t] the time( or how far into the interpolation)
     * @return the result of linear interpolation
     */
    constexpr glm::vec4 lerp(glm::vec4 a, glm::vec4 b, glm::vec4 t) {
        return glm::vec4(lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y), lerp(a.z, b.z, t.z), lerp(a.w, b.w, t.w));
    }
} 