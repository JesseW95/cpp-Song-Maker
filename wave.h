//
// Created by Jesse on 11/9/2020.
//

#ifndef PROJECT2A_WAVE_H
#define PROJECT2A_WAVE_H

#include <cmath>
#include "SoundSamples.h"
#include <string>
#include <utility>

class Wave {
public:
    std::string name;

    SoundSamples * generateSamples( float frequency, float samplerate, float duration );
    virtual float generateFunction(float time)=0;
};

//sine wave generation multiply time by 2 Pi
class SineWave : public Wave {
    float generateFunction(float time) override{
        return sinf(M_2_PI*time);
    }

public:
    SineWave(std::string _name){
        name = std::move(_name);
    }
};

//sawtooth we subtract time by integer time(so decimal is removed)
//multiply by 2 and subtract 1 to keep in -1 to 1 range
class SawtoothWave : public Wave {
    float generateFunction(float time) override{
        float t = time - (int) time;
        return 2*t-1;
    }

public:
    SawtoothWave(std::string _name){
        name = std::move(_name);
    }
};

//if time - time(rounded down) is less than 0.5 we output -1
//otherwise output 1
class SquareWave : public Wave {
    float generateFunction(float time) override{
        float t = time - floor(time);
        if(t < 0.5) return -1.0f;
        else return 1.0f;
    }

public:
    SquareWave(std::string _name){
        name = std::move(_name);
    }
};

//time - time(with decimal removed)
//if t < 0.5 we multiply it by 4 and subtract 1
class TriangleWave : public Wave {
    float generateFunction(float time) override{
        float t = time - (int) time;
        if(t< 0.5) return 4*t-1;
        return -4*t+3;
    }

public:
    TriangleWave(std::string _name){
        name = std::move(_name);
    }
};


#endif //PROJECT2A_WAVE_H
