#define _USE_MATH_DEFINES  // this must be first to use cmath 
#include <cmath>
#include <iostream>
#include <map>
#include "olcNoiseMaker.h"
#include "oscillators.h"
#include "EnvelopeADSR.h"
using namespace std;


// Global variables
atomic<double> dFrequencyOutput = 0.0;
double dVolume = 0.2;

// Generate envelope
double dStartAmplitude = 1.0;
double dAttackTime = 0.10;
double dDecayTime = 0.01;
double dSustainAmplitude = 0.8;
double dReleaseTime = 0.40;

EnvelopeADSR envelope(dStartAmplitude,
    dAttackTime,
    dDecayTime,
    dSustainAmplitude,
    dReleaseTime);


/* Note: since the make_noise function is executed continously in the main
thread through SetUserFunction(double(*func)(double)) method and its
input function only accepts as input dTime, then it is necessary to
create a global variable dFrequencyOutput to be able to change the
frequency. Other way would be to create N different functions make_noise,
each one for a different frequency. */


double make_noise(double dTime) {
    /* MAKE_NOISE generate a wave form given by the selected oscillator. */
    double dOutput = envelope.GetAmplitude(dTime) *
        1.0 * oscillator(dFrequencyOutput, dTime, OSC_SINE);
    //double dOutput = 1.0 * oscillator(dFrequencyOutput, dTime, OSC_SINE);
    return dOutput * dVolume;
}


void print_sound_hardware() {
    /* GET_SOUND_HARDWARE explores the functionality of Enumerate method from
    olcNoiseMaker, whose purpose is to return a vector of available devices for
    sound reproduction. It uses custom microsoft function for devices
    identification, if the devices is an audio output it its included into a
    vector. */

    // Get all sound hardware
    vector <wstring> devices = olcNoiseMaker<short>::Enumerate();

    // Print information
    cout << "Available devices: " << endl;
    for (size_t i = 0; i < devices.size(); i++) {
        wcout << "\t" << devices.at(i) << endl;
    }

    /*
    Notes:
    - wstring allows to use characters in unicode set, not only ascii -> to
    print it is not possible to use cout, use wcout instead.
    - device with index 0 is usually the system default device.
    */

}


void create_first_sound() {
    /*CREATE_FIRST_SOUND is the first attempt to play a sinusoidal waveform
    through the output audio device.*/
    // Get all sound hardware
    vector<wstring> devices = olcNoiseMaker<char>::Enumerate();

    // Create sound machine
    /* Parameters:
    1. Output device: devices[0] is usually the system default device
    2. Sample rate: at least double of sampled frequency (Niquist
    criteria), since max audible is 20k we use about double frequency
    40k.
    3. Number of channels: mono (1), stereo (2)
    4. Number of bits: the bigger number of bits the more accurate
    representation of waveform.
    5. Block samples: TODO
    */
    olcNoiseMaker<char> sound(devices[0], 44100, 1, 8, 512);

    /* Note: char only indicates that when type is T it will be char. It is
    used to determined the number of bits too.
    char = 8 bits
    short = 16 bits
    int = 32 bits
    */

    // Link noise function with sound machine
    sound.SetUserFunction(make_noise);
    while (1) {}

    /* Note: SetUserFunction has as input a pointer to a function. That
    function is call continously during the main thread and must have time
    as input. This time is increased by a dTimeStep at each iteration. This
    step is the inverse of the sampling rate from the object declaration.
    */
}


void piano_monophonic() {
    /* PIANO allows to play a song in A major key using the keyboard. */

    // Map of note - frequency
    map<char, double> A_major_key;
    A_major_key['A'] = 261.6;  // C
    A_major_key['S'] = 293.6;  // D
    A_major_key['D'] = 329.6;  // E
    A_major_key['F'] = 349.2;  // F
    A_major_key['G'] = 392.0;  // G
    A_major_key['H'] = 440.0;  // A
    A_major_key['J'] = 493.9;  // B
    A_major_key['K'] = 523.3;  // C
    char keys[9] = "ASDFGHJK";

    // Get all sound hardware
    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

    // Create sound object
    olcNoiseMaker<char> sound(devices[0], 44100, 1, 8, 512);

    // Link noise function with sound machine
    sound.SetUserFunction(make_noise);

    // Piano keyboard
    
    int siCurrentKey = -1;
    bool bKeyPressed = false;
    while (1) {
        bKeyPressed = false;
        for (int k = 0; k < 8; k++) {
            if (GetAsyncKeyState((unsigned char)(keys[k])) & 0x8000) {
                bKeyPressed = true;
                if (siCurrentKey != k){  // not generate new freq if equal
                    dFrequencyOutput = A_major_key[keys[k]]/2;
                    envelope.NoteOn(sound.GetTime());
                    siCurrentKey = k;
                }
            }
        }
        if (!bKeyPressed){
            if (siCurrentKey != -1) {
                envelope.NoteOff(sound.GetTime());
                siCurrentKey = -1;
            }
        }
    }

}
