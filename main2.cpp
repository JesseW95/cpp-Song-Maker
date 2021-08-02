//
// Created by Jesse on 11/19/2020.
//

#include <iostream>
#include <fstream>
#include "SoundSamples.h"
#include "wave.h"
#include "SoundIO.h"
#include <string>

using namespace std;
float getKeyFreq(float key);
int main(int argc, char *argv[]) {

    Wave *w;
    SoundSamples *s = new SoundSamples(0,44100);

    int waveSelect;
    float reverbDelay = 0, reverbAttenuation = 0;
    float atkTime, atkLevel, decTime, susTime, relTime;
    vector<SoundSamples> notes;
    int numNotes = 0;
    string fileName;

    //use file for input
    if(argc < 2){


    //Using a switch case so we can select which wave type to use.
    int pianoKey = 0;
    cout << "\nEnter piano key: ";
    cin >> pianoKey;
    while(pianoKey > -1) {
        //get inputs from user
        cout << "Enter a wave type: \n";
        cout << "(1) Sine Wave \n";
        cout << "(2) Square Wave \n";
        cout << "(3) Sawtooth Wave \n";
        cout << "(4) Triangle Wave \n";

        cin >> waveSelect;
        SoundSamples *tmp;
        switch (waveSelect) {
            case 1:
                w = new SineWave("sine");
                tmp = w->generateSamples(getKeyFreq(pianoKey), 44100, 1.0);
                break;
            case 2:
                w = new SquareWave("square");
                tmp = w->generateSamples(getKeyFreq(pianoKey), 44100, 1.0);
                break;
            case 3:
                w = new SawtoothWave("sawtooth");
                tmp = w->generateSamples(getKeyFreq(pianoKey), 44100, 1.0);
                break;
            case 4:
                w = new TriangleWave("triangle");
                tmp = w->generateSamples(getKeyFreq(pianoKey), 44100, 1.0);
                break;
            default:
                cout << "\nInvalid selection, exiting.";
                exit(0);
        }
        //apply reverb to note
        cout << "Enter reverb delay and attenuation: \n";
        cin >> reverbDelay >> reverbAttenuation;
        (*tmp).reverb2(reverbDelay, reverbAttenuation);

        //apply adsr to note
        cout << "Enter ADSR in this order (attack time, attack level, decay time, sustain level, release time): \n";
        cin >> atkTime >> atkLevel >> decTime >> susTime >> relTime;
        (*tmp).adsr(atkTime, atkLevel, decTime, susTime, relTime);

        //push note into vector and also resize the vector
        numNotes++;
        notes.resize(numNotes, *tmp);

        //for adding silence after each note
        auto *silence = new SoundSamples(11025, 44100);
        numNotes++;
        notes.resize(numNotes, *silence);

        cout << "\nEnter piano key: ";
        cin >> pianoKey;

    }
    }else{
        SoundIO::readSong(argv[1]);
        return 0;
    }
    cout << "\nFile name: ";


    cin >> fileName;
    //call SoundIO's OutputSound function, using the data acquired above
    SoundIO::OutputSong(notes, fileName);

    return 0;
}
//using wiki formula to get piano key freq.
float getKeyFreq(float key){
    float keyPow = (key-49)/12;
    return powf(2, keyPow) * 440;
}