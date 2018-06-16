/*
This code is part of the experimentation process to learn how to build a
synthesizer using C++.

Goals of this code:
- Play with the code of javidx9.
- Learn basics on sounds generation.
- Study C++.
- Understand the library olcNoiseMaker.h by javidx9.
- Create a basic prototype of synthesizer.
*/
#include <iostream>
#include <map>
#include "olcNoiseMaker.h"
#include "oscillators.h"
#include "EnvelopeADSR.h"
#include "instruments.h"

#define N_KEYS 15
using namespace std;


// Global variables
static atomic<double> dFrequencyOutput = 0.0;
static atomic<double> dVolume = 0.2;
static Instrument_t instrument = INS_TEST;
static EnvelopeADSR envelope;


static double make_noise(double dTime) {
    /* MAKE_NOISE is a wrap to have the accepted format to play the waveform
    in the main thread. */
    double dOutput = 0.0;
    dOutput = dVolume * play_instrument(instrument, envelope, dTime, dFrequencyOutput);
    return dOutput*dVolume;
}


static void change_volume() {   
    if ((GetAsyncKeyState('Z') & 0x8000) && (dVolume < 1.0)){
        dVolume = dVolume + 0.001;
    }
    else if ((GetAsyncKeyState('X') & 0x8000) && (dVolume > 0.0)){
        dVolume = dVolume - 0.001;
    }  
    wcout << "\rVolume: " << dVolume << "                        ";
}


static void display_options(){
    wcout << "Z -> volume up" << endl <<
        "X -> volume down" << endl <<
        "ESC -> change instrument " << endl;
}


static void display_keyboard() {

    // Display a keyboard
    wcout << "Keyboard schema: " << endl <<
        "|   |   | |   |   |   |   | |   | |   |   |   |   |   |" << endl <<
        "|   | W | | E |   |   | T | | Y | | U |   |   | O |   |" << endl <<
        "|   |___| |___|   |   |___| |___| |___|   |   |___|   |" << endl <<
        "|     |     |     |     |     |     |     |     |     |" << endl <<
        "|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |" << endl <<
        "|_____|_____|_____|_____|_____|_____|_____|_____|_____|" << endl << endl;
            
}


static bool choose_instrument() {
    int user_instrument = -1;
    bool bChooseAgain = true;
    bool bExit = false;
    while (bChooseAgain) {
        wcout << "\nSelect a instrument [0-BELL | 1-BELL8 | 2-HARMONICA | 3-TEST | 100-EXIT]: ";
        cin >> user_instrument;
        bChooseAgain = false;
        switch (user_instrument) {
        case 0:
            instrument = INS_BELL;
            cout << "BELL has been selected." << endl;
            break;
        case 1:
            instrument = INS_BELL8;
            cout << "BELL8 has been selected." << endl;
            break;
        case 2:
            instrument = INS_HARMONICA;
            cout << "HARMONICA has been selected." << endl;
            break;
        case 3:
            instrument = INS_TEST;
            cout << "TEST has been selected." << endl;
            break;
        case 100:
            bExit = true;
            cout << "See you soon." << endl;
            break;
        default:
            cout << "Not available instrument." << endl;
            bChooseAgain = true;
        }
    }
    return bExit;
}


int main(void) {
    // Display
    display_options();
    display_keyboard();

    // Keyboard definition
    map<char, double> note_freq;
    note_freq['A'] = 130.813;  // C
    note_freq['W'] = 138.591;  // C#
    note_freq['S'] = 146.832;  // D
    note_freq['E'] = 155.563;  // D#
    note_freq['D'] = 164.814;  // E
    note_freq['F'] = 174.614;  // F
    note_freq['T'] = 184.997;  // F#
    note_freq['G'] = 195.998;  // G
    note_freq['Y'] = 207.652;  // G#
    note_freq['H'] = 220.000;  // A
    note_freq['U'] = 233.082;  // A#
    note_freq['J'] = 246.942;  // B
    note_freq['K'] = 261.626;  // C
    note_freq['O'] = 277.183;  // C#
    note_freq['L'] = 293.665;  // D
    char keys[N_KEYS + 1] = "AWSEDFTGYHUJKOL";
    
    // Get all sound hardware
    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

    // Create sound object
    olcNoiseMaker<char> sound(devices[0], 44100, 1, 8, 512);

    // Link noise function with sound machine
    sound.SetUserFunction(make_noise);

    // Define instrument
    update_envelope(instrument, envelope);
    if (!envelope.IsCreated()) {
        cout << "Envelope has not been correctly created!" << endl;
    }

    // Let's play
    int siCurrentKey = -1;  // index of pressed key
    bool bIsKeyPressed = false;
    bool bIsPlaying = true;
    bool bExit = choose_instrument();

    while (!bExit) {    

        while (bIsPlaying) {
            bIsKeyPressed = false;

            // Select frequency corresponding to the key
            for (int k = 0; k < N_KEYS; k++) {
                if (GetAsyncKeyState((unsigned char)(keys[k])) & 0x8000) {
                    bIsKeyPressed = true;
                    if (siCurrentKey != k) {  // not generate new freq if equal
                        dFrequencyOutput = note_freq[keys[k]];
                        envelope.NoteOn(sound.GetTime());
                        siCurrentKey = k;
                    }
                }
            }

            // Unpress note
            if (!bIsKeyPressed) {
                if (siCurrentKey != -1) {
                    envelope.NoteOff(sound.GetTime());
                    siCurrentKey = -1;
                }
            }

            change_volume();
            if (GetAsyncKeyState(VK_ESCAPE)) {
                bIsPlaying = false;
            }
        }
        bExit = choose_instrument();
    }

    // Call to abort() is done due to main thread is still running.

    return 0;
}
