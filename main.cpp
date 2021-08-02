#include <iostream>
#include "SoundSamples.h"
#include "wave.h"
#include "SoundIO.h"


using namespace std;
int main() {
    Wave *w;
    SoundSamples *s;

    int waveSelect;
    float sampRate;
    float frequency;
    float duration;
    string fileName;

    //get inputs from user
    cout << "Enter a wave type: \n";
    cout << "(1) Sine Wave \n";
    cout << "(2) Square Wave \n";
    cout << "(3) Sawtooth Wave \n";
    cout << "(4) Triangle Wave \n";

    cin >> waveSelect;

    cout << "\nSample Rate: ";
    cin >> sampRate;

    cout << "\nFrequency: ";
    cin >> frequency;

    cout << "\nDuration: ";
    cin >> duration;

    cout << "\nFile name: ";
    cin >> fileName;
    //end of getting user inputs

    //Using a switch case so we can select which wave type to use.
    switch(waveSelect){
        case 1:
            w = new SineWave("sine");
            s = w->generateSamples(frequency, sampRate, duration);
            break;
        case 2:
            w = new SquareWave("square");
            s = w->generateSamples(frequency, sampRate, duration);
            break;
        case 3:
            w = new SawtoothWave("sawtooth");
            s = w->generateSamples(frequency, sampRate, duration);
            break;
        case 4:
            w = new TriangleWave("triangle");
            s = w->generateSamples(frequency, sampRate, duration);
            break;
        default:
            cout << "\nInvalid selection, exiting.";
            exit(0);
    }

    //call SoundIO's OutputSound function, using the data acquired above
    SoundIO::OutputSound(s, fileName);

    return 0;
}
