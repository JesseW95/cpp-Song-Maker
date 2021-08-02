//
// Created by Jesse on 11/9/2020.
//

#include "SoundIO.h"
#include "wave.h"
#include <iostream>
#include <fstream>
#include <iomanip>
//create file with filename
//iterate through SoundSamples until SoundSample's length
//write soundSample's sample at i each iteration
void SoundIO::OutputSound(SoundSamples *samples, string filename) {
    ofstream fileOut(filename);
    for(int i = 0; i < samples->length(); i++){
        fileOut << (*samples)[i] << "\n";
    }
    fileOut.close();
}

void SoundIO::OutputSong(vector<SoundSamples> notes, string filename) {
    ofstream fileOut(filename);
    //loop through all the notes in the vector
    for(SoundSamples note : notes){
        for(int i = 0; i < note.length(); i++){
            //here we set precision to 5 so we dont get weird scientific notation values.
            fileOut << fixed << setprecision(6) << note[i] << "\n";
        }
    }
    fileOut.close();
}

//Extra stuff I made for fun

//using wiki formula to get piano key freq.
float getKeyFreqFile(float key){
    float keyPow = (key-49)/12;
    return powf(2, keyPow) * 440;
}

void SoundIO::readSong(string filename) {
    fstream rf(filename);
    string line;
    if (rf.is_open())
    {
        Wave *w;
        SoundSamples *tmp;
        int numNotes = 0;
        string fileName;
        vector<SoundSamples> notes;
        float reverbDelay = 0, reverbAttenuation = 0;
        float atkTime, atkLevel, decTime, susTime, relTime;
        while ( getline(rf,line) )
        {
            //get piano key and exit if -1
            int pianoKey = stoi(line);
            if(pianoKey == -1){
                break;
            }
            //get wave selection
            getline(rf,line);
            int waveSelect = stoi(line);
            switch(waveSelect){
                case 1:
                    w = new SineWave("sine");
                    tmp = w->generateSamples(getKeyFreqFile(pianoKey), 44100, 1.0);
                    break;
                case 2:
                    w = new SquareWave("square");
                    tmp = w->generateSamples(getKeyFreqFile(pianoKey), 44100, 1.0);
                    break;
                case 3:
                    w = new SawtoothWave("sawtooth");
                    tmp = w->generateSamples(getKeyFreqFile(pianoKey), 44100, 1.0);
                    break;
                case 4:
                    w = new TriangleWave("triangle");
                    tmp = w->generateSamples(getKeyFreqFile(pianoKey), 44100, 1.0);
                    break;
                default:
                    cout << "\nInvalid selection, exiting.";
                    exit(0);
            }

            //reverb info
            getline(rf,line);
            reverbDelay = stof(line);
            getline(rf,line);
            reverbAttenuation = stof(line);
            (*tmp).reverb2(reverbDelay, reverbAttenuation);

            //adsr info
            getline(rf,line);
            atkTime = stof(line);

            getline(rf,line);
            atkLevel = stof(line);

            getline(rf,line);
            decTime = stof(line);

            getline(rf,line);
            susTime = stof(line);

            getline(rf,line);
            relTime = stof(line);

            (*tmp).adsr(atkTime, atkLevel, decTime, susTime, relTime);
            //add note to vector
            //push note into vector and also resize the vector
            numNotes++;
            notes.resize(numNotes, *tmp);

            //for adding silence after each note
            auto *silence = new SoundSamples(11025,44100);
            numNotes++;
            notes.resize(numNotes, *silence);
        }
        cout << "\nFile name: ";


        cin >> fileName;
        //call SoundIO's OutputSound function, using the data acquired above
        OutputSong(notes, fileName);
        rf.close();
    }
}
