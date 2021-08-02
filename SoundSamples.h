//
// Created by Jesse on 11/8/2020.
//

#ifndef PROJECT2A_SOUNDSAMPLES_H
#define PROJECT2A_SOUNDSAMPLES_H

class SoundSamples{


    float * samples;
    int numSamples = 0;
    float SampleRate = 8000;
public:
    SoundSamples();
    SoundSamples(float *_samples, int _numSamples, float _SampleRate);
    SoundSamples(int _numSamples, int _sampleRate);
    SoundSamples(const SoundSamples &other);

    SoundSamples operator=(const SoundSamples& other);
    SoundSamples operator+(const SoundSamples& other);
    float &operator[](int);
    int length();


    float getSampleRate(){ return SampleRate; }

    void reverb2( float delay, float attenuation);
    void adsr( float atime, float alevel, float dtime, float slevel, float rtime);
};



#endif //PROJECT2A_SOUNDSAMPLES_H
