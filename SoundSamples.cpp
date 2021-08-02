//
// Created by Jesse on 11/9/2020.
//
#include <cstdlib>
#include <stdexcept>
#include "SoundSamples.h"

SoundSamples::SoundSamples(int _numSamples, int _sampleRate) {
    SampleRate = _sampleRate;
    numSamples = _numSamples;
    //we use new float with size of number of samples to free up memory on heap
    float *arr = new float[numSamples];

    //iterate through all the samples in _samples and set arr at i to them.
    //afterwards set samples = arr
    for(int i = 0; i < _numSamples; i++){
        arr[i] = 0;
    }
    samples = arr;
}

SoundSamples::SoundSamples( float *_samples, int _numSamples, float _SampleRate) {
    SampleRate = _SampleRate;
    numSamples = _numSamples;
    //we use new float with size of number of samples to free up memory on heap
    float *arr = new float[numSamples];

    //iterate through all the samples in _samples and set arr at i to them.
    //afterwards set samples = arr
    for(int i = 0; i < _numSamples; i++){
        arr[i] =  _samples[i];
    }
    samples = arr;
}

SoundSamples SoundSamples::operator=(const SoundSamples &other) {
    if(this == &other)
        return *this;

    delete[] samples;

    SampleRate = other.SampleRate;
    numSamples = other.numSamples;
    if(other.samples){
        //declare a new float with size = number of samples
        float *arr = new float[numSamples];
        for(int i = 0; i < numSamples; i++){
            arr[i] = other.samples[i];
        }
        samples = arr;
    }else{
        samples = nullptr;
    }
    return *this;
}

SoundSamples::SoundSamples() : numSamples(0), SampleRate(8000) {

}

SoundSamples::SoundSamples(const SoundSamples &other) {
    SampleRate = other.SampleRate;
    numSamples = other.numSamples;
    if(other.samples){
        //declare a new float with size = number of samples
        float *arr = new float[numSamples];
        for(int i = 0; i < numSamples; i++){
            arr[i] = other.samples[i];
        }
        samples = arr;
    }else{
        samples = nullptr;
    }
}

//we need to deref the sample for this to work
//gets samples at provided index
float &SoundSamples::operator[](int ind) {
    //check if provided int is within range of the array
    if(ind >= numSamples || ind < 0)
        exit(0);

    return samples[ind];
}

//creates a new SoundSample with the 2 numSamples add
//iterate through first SoundSample setting each arr[i] to samples[i]
//next to start off at the end of samples we add numSamples onto i in the arr index.
SoundSamples SoundSamples::operator+(const SoundSamples &other) {
    int tmp = numSamples + other.numSamples;
    float *arr = new float[tmp];

    if(other.SampleRate != SampleRate){
        throw std::runtime_error("Sample rates must be the same.");
    }

    for(int i = 0; i < numSamples; i++){
        arr[i] = samples[i];
    }
    for(int i = 0; i < other.numSamples; i++){
        arr[i+numSamples] = other.samples[i];
    }

    return SoundSamples(arr, tmp, SampleRate);
}

int SoundSamples::length() {
    return numSamples;
}

void SoundSamples::reverb2(float delay, float attenuation) {
    int sdelay = delay;
    float *arr = new float[numSamples];
    for(int i = 0; i < numSamples; i++){
        if(i -delay *getSampleRate() < 0){
            arr[i] = samples[i];
        }else{
            arr[i] = samples[i] + arr[i-sdelay+1]*attenuation;
        }
    }
    samples = arr;
}

void SoundSamples::adsr(float atime, float alevel, float dtime, float slevel, float rtime) {
    int attackEndSample = atime;
    int decayEndSample = attackEndSample + (dtime);
    int releaseBeginSample = (numSamples - rtime);
    //ifs checking if any of above vars > numSamples or < 0 (out of bounds)
    if(attackEndSample > numSamples || decayEndSample > numSamples || releaseBeginSample > numSamples){
        throw std::invalid_argument("Input values exceeded number of samples in current SoundSample.");
    }


    //loop for attack
    for(int i = 0; i < attackEndSample; i++){
        samples[i] *= ((alevel)/(attackEndSample)) * (i);
    }

    //loop for decay
    //here we have to interpolate between attack and slevel
    //interpolation formula yp = y0 + ((y1-y0)/(x1-x0))*(xp - x0)
    //where yp is current sound multplier
    // y0 & y1 are alevel & slevel, x0 & x1 are the start and end points, and xp is current index i
    for(int i = attackEndSample; i < decayEndSample; i++){
        samples[i] *= alevel - ((alevel - slevel)/(decayEndSample - attackEndSample)) * (i - attackEndSample);
    }

    //loop for sustain
    for(int i = decayEndSample; i < releaseBeginSample; i++){
        samples[i] *= slevel;
    }

    //loop for release
    //use the linear interpolation method from decay, but since we are interpolating to 0, we dont need to set a
    //y0 in the middle section. Add 1 onto end i to account to first iteration.
    for(int i = releaseBeginSample; i < numSamples; i++){
        samples[i] *= slevel - ((slevel)/(numSamples - releaseBeginSample)) * (i+1 - releaseBeginSample);
    }

}
