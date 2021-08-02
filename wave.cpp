//
// Created by Jesse on 11/9/2020.
//

#include "wave.h"


SoundSamples *Wave::generateSamples(float frequency, float samplerate, float duration) {
    int length = samplerate*duration;
    //initialize array to all 0s
    SoundSamples * arr = new SoundSamples(length, samplerate);
    //curTime is used to keep track of where we are on the wave
    float curTime = 0.00;
    for(int i = 0; i <length; i++){
        //we multiply curTime by frequency for amplitude of the wave
        //ie. how long it stays going up or down.
       arr->operator[](i) = generateFunction(curTime*frequency);
       curTime += 1/samplerate;
    }


    return arr;
}


