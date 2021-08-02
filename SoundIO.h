//
// Created by Jesse on 11/9/2020.
//

#ifndef PROJECT2A_SOUNDIO_H
#define PROJECT2A_SOUNDIO_H


#include "SoundSamples.h"
#include <string>
#include <vector>
using namespace std;
class SoundIO {
public:
    static void OutputSound(SoundSamples *samples, string filename );
    static void OutputSong(vector<SoundSamples> notes, string filename);
    static void readSong(string filename);
};


#endif //PROJECT2A_SOUNDIO_H
