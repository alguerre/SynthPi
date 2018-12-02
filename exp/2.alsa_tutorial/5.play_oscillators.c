#define ALSA_PCM_NEW_HW_PARAMS_AP
#include <alsa/asoundlib.h>
#include <math.h>
#include <wiringPi.h>
#define SND_PCM_RATE_STD 44100
#define SND_PCM_CHANNEL_MONO 1
#define SND_PCM_CHANNEL_STEREO 2
#define SND_PCM_PERIOD_SIZE 4 
#define FREQ_C 130.813 
#define FREQ_D 146.832
#define FREQ_E 164.814
#define FREQ_F 174.614
#define FREQ_G 195.998
#define FREQ_A 220.000
#define PIN_KEY_C 25
#define PIN_KEY_D 24
#define PIN_KEY_E 23
#define PIN_KEY_F 22
#define PIN_KEY_G 21
#define PIN_KEY_A 29
#define PIN_OSC_MSB 2
#define PIN_OSC_LSB 0

typedef enum {
    OSC_SINE,
    OSC_SQUARE,
    OSC_TRIANGLE,
    OSC_SAW_ANA,
    OSC_SAW_DIG,
    OSC_NOISE
} Osc_t;


double oscillator(double dFreq, double dTime, Osc_t eType) {
    /* OSCILLATOR returns the the amplitude of the specified oscillator eType
    at a given moment given its frequency.*/

    // Initialization
    double dOutput = 0.0;

    // Frequency oscillation times time
    double dW_T = dFreq * 2.0 * M_PI * dTime; 

    // Oscillator definitions
    switch (eType) {
    case OSC_SINE:
        dOutput = sin(dW_T);
        break;

    case OSC_SQUARE:
        dOutput = sin(dW_T) > 0 ? 1.0 : -1.0;
        break;

    case OSC_TRIANGLE:
        dOutput = asin(sin(dW_T)) * M_2_PI;
        break;

    case OSC_SAW_ANA:  // summation of Fourier harmonics
        dOutput = 0.0;

        for (int n = 1; n < 50; n++)  // 50 armonics are used by default
            dOutput += (sin(n * dFreq * 2.0 * M_PI * dTime)) / ((double) n);

        dOutput = dOutput * M_2_PI;
        break;

    case OSC_SAW_DIG:  // computation of sawtooth signal arithmetically
        dOutput = M_2_PI * (dFreq * M_PI * fmod(dTime, 1.0 / dFreq) - M_PI_2);
        break;

    case OSC_NOISE: 
        return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
        break;

    default:
        dOutput = 0.0;
    }

    return dOutput;
}

int main(void){

    // PCM variables initialization
    int si_error = 0;
    snd_pcm_t *pcm_handle = NULL;
    snd_pcm_hw_params_t *hw_params = NULL;
    unsigned int ui_rate = SND_PCM_RATE_STD;

    // Sound generation variables initialization
    double d_buffer[SND_PCM_PERIOD_SIZE] = {0};
    double d_time = 0.0;
    const double d_time_elapsed = 1.0/((double)SND_PCM_RATE_STD);
    double d_mixed_output = 0.0;
    Osc_t e_oscillator = OSC_SINE;

    // Initialize wiringPi
    wiringPiSetup();
    pinMode(PIN_KEY_C, INPUT);
    pinMode(PIN_KEY_D, INPUT);
    pinMode(PIN_KEY_E, INPUT);
    pinMode(PIN_KEY_F, INPUT);
    pinMode(PIN_KEY_G, INPUT);
    pinMode(PIN_KEY_A, INPUT);
    pinMode(PIN_OSC_MSB, INPUT);
    pinMode(PIN_OSC_LSB, INPUT);    

    // Open PCM device for playback
    pcm_handle = (snd_pcm_t *) malloc(sizeof(snd_pcm_t*));
    si_error = snd_pcm_open(&pcm_handle, 
                            "default", 
                            SND_PCM_STREAM_PLAYBACK, 
                            0); 
    if (si_error < 0){
        fprintf(stderr, 
            "Unable to open pcm device: %s\n", 
            snd_strerror(si_error));
    }

    // Set hardware and software parameters
    snd_pcm_hw_params_malloc(&hw_params);

    si_error = snd_pcm_hw_params_any(
        pcm_handle,
        hw_params
    );
    if (si_error < 0){
        fprintf(stderr, "Can not configure this PCM device.\n");
        snd_pcm_close(pcm_handle);
        exit(1);
    }
    
    snd_pcm_hw_params_set_access( 
        pcm_handle,
        hw_params,
        SND_PCM_ACCESS_RW_INTERLEAVED
    );

    snd_pcm_hw_params_set_format(
        pcm_handle,
        hw_params,
        SND_PCM_FORMAT_FLOAT64_LE
    );

    snd_pcm_hw_params_set_channels(
        pcm_handle,
        hw_params,
        SND_PCM_CHANNEL_MONO
    );

    snd_pcm_hw_params_set_rate_near(
        pcm_handle,
        hw_params,
        &ui_rate,
        NULL
    );

    // Write new parameters to the driver
    si_error = snd_pcm_hw_params(pcm_handle, hw_params);
    if (si_error < 0){
        fprintf(stderr, "Unable to set hw parameters: %s\n", snd_strerror(si_error));
        exit(1);
    }

    // Generate and play sounds
    while(1){
        // Select oscillator
        e_oscillator = digitalRead(PIN_OSC_MSB)*2 + digitalRead(PIN_OSC_LSB);

        for (int si_frame = 0; si_frame < SND_PCM_PERIOD_SIZE; si_frame++){

            // Initialization
            d_time = d_time + d_time_elapsed;
            d_mixed_output = 0.0;
            
            // Check key note
            if (digitalRead(PIN_KEY_C) == 1){
                d_mixed_output += oscillator(FREQ_C, d_time, e_oscillator);
            }
            if (digitalRead(PIN_KEY_D) == 1){
                d_mixed_output += oscillator(FREQ_D, d_time, e_oscillator);
            }
            if (digitalRead(PIN_KEY_E) == 1){
                d_mixed_output += oscillator(FREQ_E, d_time, e_oscillator);
            }
            if (digitalRead(PIN_KEY_F) == 1){
                d_mixed_output += oscillator(FREQ_F, d_time, e_oscillator);
            }
            if (digitalRead(PIN_KEY_G) == 1){
                d_mixed_output += oscillator(FREQ_G, d_time, e_oscillator);
            }
            if (digitalRead(PIN_KEY_A) == 1){
                d_mixed_output += oscillator(FREQ_A, d_time, e_oscillator);
            }

            // Generate wave
            d_buffer[si_frame] = d_mixed_output;
        }

        // Write PCM buffer
        snd_pcm_writei(pcm_handle, d_buffer, SND_PCM_PERIOD_SIZE);
    }

    snd_pcm_close(pcm_handle);
    return 0;
}

