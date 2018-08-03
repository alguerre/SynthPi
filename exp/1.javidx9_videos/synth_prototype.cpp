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
#include "constants.h"
#include "instruments/bell8.h"
#include "instruments/bell.h"
#include "instruments/organ.h"
#include "instruments/harmonica.h"
#include "instruments/debug.h"
using namespace std;


// Global variables
static atomic<double> dFrequencyOutput = 0.0;
static atomic<double> dVolume = INIT_VOLUME;
static Instrument_t instrument = INS_DEBUG;
mutex mtVolume;
Instrument *pobInstrument = NULL;


static double make_noise(double dTime) {
    /* MAKE_NOISE is a wrap to have the accepted format to play the waveform
    in the main thread. */
    double dOutput = 0.0;

    if (pobInstrument == NULL)
        return 0;

    dOutput = pobInstrument->Play(dTime, dFrequencyOutput); 

    if (dVolume < VOLUME_MIN_LIMIT)
        dOutput = 0;

    return dOutput * pow(10.0, dVolume) / 10.0;
}


static void change_volume() {   
    if ((GetAsyncKeyState('Z') & 0x8000) && (dVolume < MAX_VOLUME)){
        mtVolume.lock();
        dVolume = dVolume + DELTA_VOLUME;
        mtVolume.unlock();
    }
    else if ((GetAsyncKeyState('X') & 0x8000) && (dVolume > MIN_VOLUME)){
        mtVolume.lock();
        dVolume = dVolume - DELTA_VOLUME;
        mtVolume.unlock();
    }  

    if (dVolume > 1.0)
        dVolume = 1.0;
    else if (dVolume < 0.0)
        dVolume = 0.0;

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
    // Delete previous instrument   
    if (pobInstrument != NULL) {
        delete pobInstrument;
        pobInstrument = NULL;
    }
    dFrequencyOutput = 0.0;  // stop previous sound

    // Instrument selection
    int user_instrument = -1;
    bool bChooseAgain = true;
    bool bExit = false;
    while (bChooseAgain) {
        wcout << "\nSelect a instrument [0-BELL | 1-BELL8 | 2-HARMONICA | 3-ORGAN | 4-DEBUG | 100-EXIT]: ";
        cin >> user_instrument;
        bChooseAgain = false;
        switch (user_instrument) {
        case INS_BELL:
            pobInstrument = new Bell();
            instrument = INS_BELL;
            cout << "BELL has been selected." << endl;
            break;
        case INS_BELL8:
            pobInstrument = new Bell8();
            instrument = INS_BELL8;
            cout << "BELL8 has been selected." << endl;
            break;
        case INS_HARMONICA:
            pobInstrument = new Harmonica();
            instrument = INS_HARMONICA;
            cout << "HARMONICA has been selected." << endl;
            break;
        case INS_ORGAN:
            pobInstrument = new Organ();
            instrument = INS_ORGAN;
            cout << "ORGAN has been selected." << endl;
            break;
        case INS_DEBUG:
            pobInstrument = new Debug();
            instrument = INS_DEBUG;
            cout << "TEST has been selected." << endl;
            break;
        case 100:
            bExit = true;
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
    cout << "bDriverExit = " << bDriverExit << endl;
    // Keyboard definition
    map<char, double> note_freq;
    note_freq['A'] = FREQ_C1;   // C
    note_freq['W'] = FREQ_Cs1;  // C#
    note_freq['S'] = FREQ_D1;   // D
    note_freq['E'] = FREQ_Ds1;  // D#
    note_freq['D'] = FREQ_E1;   // E
    note_freq['F'] = FREQ_F1;   // F
    note_freq['T'] = FREQ_Fs1;  // F#
    note_freq['G'] = FREQ_G1;   // G
    note_freq['Y'] = FREQ_Gs1;  // G#
    note_freq['H'] = FREQ_A1;   // A
    note_freq['U'] = FREQ_As1;  // A#
    note_freq['J'] = FREQ_B1;   // B
    note_freq['K'] = FREQ_C2;   // C
    note_freq['O'] = FREQ_Cs2;  // C#
    note_freq['L'] = FREQ_D2;   // D
    char keys[N_KEYS + 1] = KEYS_SET;
    
    // Get all sound hardware
    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

    // Create sound object
    olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);
    
    // Let's play
    int siCurrentKey = -1;  // index of pressed key
    bool bIsKeyPressed = false;
    bool bIsPlaying = true;
    bool bExit = choose_instrument();
    sound.SetUserFunction(make_noise); // Link noise function with sound machine

    while (!bExit) {    

        while (bIsPlaying) {
            bIsKeyPressed = false;

            // Select frequency corresponding to the key
            for (int k = 0; k < N_KEYS; k++) {
                if (GetAsyncKeyState((unsigned char)(keys[k])) & 0x8000) {
                    bIsKeyPressed = true;
                    if (siCurrentKey != k) {  // not generate new freq if equal
                        dFrequencyOutput = note_freq[keys[k]];
                        pobInstrument->obEnvelope.NoteOn(sound.GetTime());
                        wcout << "\rVolume: " << dVolume << "      Note On : " << sound.GetTime() << "s " << dFrequencyOutput << "Hz";                        
                        siCurrentKey = k;
                    }
                }
            }

            // Unpress note
            if (!bIsKeyPressed) {
                if (siCurrentKey != -1) {
                    pobInstrument->obEnvelope.NoteOff(sound.GetTime());
                    siCurrentKey = -1;
                }
            }

            change_volume();
            if (GetAsyncKeyState(VK_ESCAPE)) {
                bIsPlaying = false;
            }
        }

        // Select new instrument or exit
        sound.SetUserFunction(0);  // stop sending output from make_noise
        bExit = choose_instrument();
        bIsPlaying = true;
        sound.SetUserFunction(make_noise);  // restart sounding
    }

    // Wait until driver has detached its thread
    bDriverExit = true;
    WaitForSingleObject(ghSemaphoreDriver, INFINITE);

    return 0;
}
