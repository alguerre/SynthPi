#pragma once

#ifndef _CONSTANTS_h
#define _CONSTANTS_h

// Audio driver
#define AUDIOTYPE short
#define N_SAMPLES_BLOCK 512
#define N_BLOCK 8
#define SAMPLE_RATE 44100
#define N_CHANNEL 1

// Envelope
#define MINIMUM_AMPLITUDE 0.001

// Volume
#define INIT_VOLUME 0.5
#define MAX_VOLUME 1.0
#define MIN_VOLUME 0.0
#define DELTA_VOLUME 0.001
#define VOLUME_MIN_LIMIT 0.05

// Frequencies
#define FREQ_C1   130.813  // C
#define FREQ_Cs1  138.591  // C#
#define FREQ_D1   146.832  // D
#define FREQ_Ds1  155.563  // D#
#define FREQ_E1   164.814  // E
#define FREQ_F1   174.614  // F
#define FREQ_Fs1  184.997  // F#
#define FREQ_G1   195.998  // G
#define FREQ_Gs1  207.652  // G#
#define FREQ_A1   220.000  // A
#define FREQ_As1  233.082  // A#
#define FREQ_B1   246.942  // B
#define FREQ_C2   261.626  // C
#define FREQ_Cs2  277.183  // C#
#define FREQ_D2   293.665  // D

// Keys
#define N_KEYS 15
#define KEYS_SET "AWSEDFTGYHUJKOL"

// Instruments
typedef enum {
    INS_NONE = 0,
    INS_BELL,
    INS_BELL8,
    INS_HARMONICA,
    INS_ORGAN,
    INS_DRUM_KICK,
    INS_DRUM_HIHAT,
    INS_DRUM_SNARE,
    INS_DEBUG
} Instrument_t;

// Drums
#define N_DRUMS 3
#define KEYS_DRUMS_SET "789"
#define FREQ_KICK 40.317
#define FREQ_HIHAT 161.270
#define FREQ_SNARE 80.635

#endif