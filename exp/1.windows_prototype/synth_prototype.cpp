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
#include "instrument.h"
#include "constants.h"

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

    wcout << "\rVolume: " << dVolume << "   Note: " << dFrequencyOutput << "Hz";
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
    bool bExit = false;
    ChooseInstrument *pobChooseInstrument = new ChooseInstrument();
    pobInstrument = pobChooseInstrument->getInstrument();
    if (pobInstrument == NULL) {
        bExit = true;
    }

    return bExit;
}


int main(void) {
    // Display
    display_options();
    display_keyboard();

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

    while (!bExit) {    
        sound.SetUserFunction(make_noise);  // Link noise function with sound machine

        while (bIsPlaying) {
            bIsKeyPressed = false;

            // Select frequency corresponding to the key
            for (int k = 0; k < N_KEYS; k++) {
                if (GetAsyncKeyState((unsigned char)(keys[k])) & 0x8000) {
                    bIsKeyPressed = true;
                    if (siCurrentKey != k) {  // not generate new freq if equal
                        dFrequencyOutput = note_freq[keys[k]];
                        pobInstrument->obEnvelope.NoteOn(sound.GetTime());            
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
    }

    // Wait until driver has detached its thread
    bDriverExit = true;
    WaitForSingleObject(ghSemaphoreDriver, INFINITE);

    return 0;
}
