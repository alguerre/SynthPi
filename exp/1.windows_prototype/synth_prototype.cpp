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
static atomic<double> dVolume = INIT_VOLUME;
mutex ghNotes;
mutex ghVolume;
Instrument *pobInstrument[N_KEYS] = { NULL };
Instrument *pobDrums[N_DRUMS] = { NULL, NULL, NULL };


static double make_noise(int siChannel, double dTime) {
    /* MAKE_NOISE is a wrap to have the accepted format to play the waveform
    in the main thread of NoiseMaker.cpp */

    // Initialization
    double dMixedOutput = 0.0;
    double pdFreqs[N_KEYS] = { FREQ_C1,  FREQ_Cs1, FREQ_D1, FREQ_Ds1, FREQ_E1,
        FREQ_F1,  FREQ_Fs1, FREQ_G1, FREQ_Gs1, FREQ_A1,
        FREQ_As1, FREQ_B1,  FREQ_C2, FREQ_Cs2, FREQ_D2 };

    if (pobInstrument == NULL)
        return 0;

    // Mix all active sounds
    ghNotes.lock();
    for (int siKey = 0; siKey < N_KEYS; siKey++) {
        dMixedOutput += pobInstrument[siKey]->Play(dTime, pdFreqs[siKey]);
    }  
    for (int siDrums = 0; siDrums < N_DRUMS; siDrums++) {
        dMixedOutput += pobDrums[siDrums]->Play(dTime, 0.0);
    }
    ghNotes.unlock();

    // Limit of volume
    if (dVolume < VOLUME_MIN_LIMIT)
        dMixedOutput = 0;

    // Output with adapted volume for a linear change behaviour listening
    return dMixedOutput * pow(10.0, dVolume) / 10.0;
}


static void change_volume() { 
    /*CHANGE_VOLUME changes the global variable dVolume when Z or X keys are
    pressed, they are related to the output wave intensity.*/

    ghVolume.lock();

    if ((GetAsyncKeyState('Z') & 0x8000) && (dVolume < MAX_VOLUME)){
        dVolume = dVolume + DELTA_VOLUME;
    }
    else if ((GetAsyncKeyState('X') & 0x8000) && (dVolume > MIN_VOLUME)){
        dVolume = dVolume - DELTA_VOLUME;
    }  

    if (dVolume > 1.0)
        dVolume = 1.0;
    else if (dVolume < 0.0)
        dVolume = 0.0;

    ghVolume.unlock();

    wcout << "\rVolume: " << dVolume;
}


static void display_keyboard() {
    /* DISPLAY_KEYBOARD prints the keyboard schema of our piano.*/

    wcout << "Keyboard schema: " << endl <<
        "                              |     |     |     |      " << endl <<
        "                              |  7  |  8  |  9  |      " << endl <<
        "                              |_____|_____|_____|      " << endl <<
        "|   |   | |   |   |   |   | |   | |   |   |   |   |   |" << endl <<
        "|   | W | | E |   |   | T | | Y | | U |   |   | O |   |" << endl <<
        "|   |___| |___|   |   |___| |___| |___|   |   |___|   |" << endl <<
        "|     |     |     |     |     |     |     |     |     |" << endl <<
        "|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |" << endl <<
        "|_____|_____|_____|_____|_____|_____|_____|_____|_____|" << endl << 
        endl;

    wcout << "Z -> volume up" << endl <<
        "X -> volume down" << endl <<
        "ESC -> change instrument " << endl;
}


void create_drums() {
    /* CREATE_DRUMS create the corresponding instruments for a global array
    consisting of a type of drum per element.*/
    ChooseInstrument *pobChooseInstrument = NULL;
    
    pobChooseInstrument = new ChooseInstrument(INS_DRUM_KICK);
    pobDrums[0] = pobChooseInstrument->GetInstrument();

    pobChooseInstrument = new ChooseInstrument(INS_DRUM_HIHAT);
    pobDrums[1] = pobChooseInstrument->GetInstrument();

    pobChooseInstrument = new ChooseInstrument(INS_DRUM_SNARE);
    pobDrums[2] = pobChooseInstrument->GetInstrument();
}


static bool choose_instrument() {
    /* CHOOSE_INSTRUMENT creates one instrument per note and store them in
    the global array pobInstrument. A menu to choose the instrument will appear
    from ChoosInstrument class, if the EXIT instrument is selected then 
    instrument pointer will be null and the program will finish.*/

    // Delete previous instrument
    for (int siInstrument = 0; siInstrument < N_KEYS; siInstrument++) {
        if (pobInstrument[siInstrument] != NULL) {
            delete pobInstrument[siInstrument];
            pobInstrument[siInstrument] = NULL;
        }
    }

    // Instrument selection
    bool bExit = false;
    ChooseInstrument *pobChooseInstrument = NULL;
    Instrument_t eInstrumentId = INS_NONE;

    // Fist instrument definition
    pobChooseInstrument = new ChooseInstrument();
    pobInstrument[0] = pobChooseInstrument->GetInstrument();
    eInstrumentId = pobChooseInstrument->GetInstrumentId();

    // Remaining instruments
    if (eInstrumentId != INS_NONE) {
        for (int siInstrument = 1; siInstrument < N_KEYS; siInstrument++) {
            pobChooseInstrument = new ChooseInstrument(eInstrumentId);
            pobInstrument[siInstrument] = pobChooseInstrument->GetInstrument();
        }
        bExit = false;
    }
    else {
        bExit = true;
    }

    return bExit;
}


int main(void) {
    // Display
    display_keyboard();

    // Keyboard definition
    map<char, double> mpNoteFreq;
    mpNoteFreq['A'] = FREQ_C1;   // C
    mpNoteFreq['W'] = FREQ_Cs1;  // C#
    mpNoteFreq['S'] = FREQ_D1;   // D
    mpNoteFreq['E'] = FREQ_Ds1;  // D#
    mpNoteFreq['D'] = FREQ_E1;   // E
    mpNoteFreq['F'] = FREQ_F1;   // F
    mpNoteFreq['T'] = FREQ_Fs1;  // F#
    mpNoteFreq['G'] = FREQ_G1;   // G
    mpNoteFreq['Y'] = FREQ_Gs1;  // G#
    mpNoteFreq['H'] = FREQ_A1;   // A
    mpNoteFreq['U'] = FREQ_As1;  // A#
    mpNoteFreq['J'] = FREQ_B1;   // B
    mpNoteFreq['K'] = FREQ_C2;   // C
    mpNoteFreq['O'] = FREQ_Cs2;  // C#
    mpNoteFreq['L'] = FREQ_D2;   // D
    char pcKeys[N_KEYS + 1] = KEYS_SET;
    char pcKeysDrums[N_DRUMS + 1] = KEYS_DRUMS_SET;

    // Create sound object
    vector<wstring> devices = olcNoiseMaker<AUDIOTYPE>::Enumerate();
    olcNoiseMaker<AUDIOTYPE> sound(devices[0], 
        SAMPLE_RATE,
        N_CHANNEL,
        N_BLOCK, 
        N_SAMPLES_BLOCK);

    // Let's play
    int siCurrentKey[N_KEYS] = { -1 };  // index of pressed key
    int siActiveDrum[N_DRUMS] = { -1,-1,-1 };  // index of pressed drum
    bool bIsPlaying = true;
    bool bExit = choose_instrument();
    create_drums();

    while (!bExit) {    
        // Link noise function with sound machine
        sound.SetUserFunction(make_noise);  

        while (bIsPlaying) {

            // Play instrument
            for (int k = 0; k < N_KEYS; k++) {
                double dTimeNow = sound.GetTime();
                ghNotes.lock();
                if (GetAsyncKeyState(pcKeys[k]) & 0x8000) {
                    if (siCurrentKey[k] != k) {
                        pobInstrument[k]->NoteOn(dTimeNow);
                        siCurrentKey[k] = k;
                    }
                }
                else {  // Unpress note
                    if (siCurrentKey[k] != -1) {
                        pobInstrument[k]->NoteOff(dTimeNow);
                        siCurrentKey[k] = -1;
                    }
                }
                ghNotes.unlock();
            }

            // Play drums
            for (int k = 0; k < N_DRUMS; k++) {
                double dTimeNow = sound.GetTime();
                ghNotes.lock();
                if (GetAsyncKeyState(pcKeysDrums[k]) & 0x8000){
                    if (siActiveDrum[k] != k) {
                        pobDrums[k]->NoteOn(dTimeNow);
                        siActiveDrum[k] = k;
                    }
                }
                else {  // Unpress note
                    if (siActiveDrum[k] != -1) {
                        pobDrums[k]->NoteOff(dTimeNow);
                        siActiveDrum[k] = -1;
                    }
                }
                ghNotes.unlock();
            }

            // Change volume
            change_volume();

            // Stop playing current instrument
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
