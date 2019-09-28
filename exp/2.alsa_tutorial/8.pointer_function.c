#define ALSA_PCM_NEW_HW_PARAMS_AP
#include <alsa/asoundlib.h>
#include <math.h>
#include <wiringPi.h>
#include <pthread.h>
#include <semaphore.h>
#define SND_PCM_RATE_STD 44100
#define SND_PCM_CHANNEL_MONO 1
#define SND_PCM_CHANNEL_STEREO 2
#define SND_PCM_PERIOD_SIZE 4 
#define FREQ_C 261.626
#define FREQ_D 293.664
#define FREQ_E 329.628
#define FREQ_F 349.228
#define FREQ_G 391.996
#define FREQ_A 440.000
#define PIN_KEY_C 29
#define PIN_KEY_D 28
#define PIN_KEY_E 27
#define PIN_KEY_F 26
#define PIN_KEY_G 21
#define PIN_KEY_A 3
#define PIN_OSC_MSB 24 
#define PIN_OSC_LSB 25


typedef enum {
    OSC_SINE,
    OSC_SQUARE,
    OSC_TRIANGLE,
    OSC_SAW_ANA,
    OSC_SAW_DIG,
    OSC_NOISE
} Osc_t;


// Gloval varialbes definition
double gd_time = 0;
double gd_time_elapsed = 0.0;
double gd_freq = 0.0;
Osc_t ge_oscillator = OSC_SINE;
sem_t gmx_measurements;


double oscillator(double dTime, Osc_t eType) {
    /* OSCILLATOR returns the the amplitude of the specified oscillator eType
    at a given moment given its frequency.*/

    // Initialization
    double dOutput = 0.0;

    // Frequency oscillation times time
    double dW_T = gd_freq * 2.0 * M_PI * dTime; 

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
            dOutput += (sin(n * gd_freq * 2.0 * M_PI * dTime)) / ((double) n);

        dOutput = dOutput * M_2_PI;
        break;

    case OSC_SAW_DIG:  // computation of sawtooth signal arithmetically
        dOutput = M_2_PI * (gd_freq * M_PI * fmod(dTime, 1.0 / gd_freq) - M_PI_2);
        break;

    case OSC_NOISE: 
        return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
        break;

    default:
        dOutput = 0.0;
    }

    return dOutput;
}


snd_pcm_t * audio_driver_init(void){
    // PCM variables initialization
    int si_error = 0;
    snd_pcm_t *pcm_handle = NULL;
    snd_pcm_hw_params_t *hw_params = NULL;
    unsigned int ui_rate = SND_PCM_RATE_STD;

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

  return pcm_handle;
}


int audio_driver_play(snd_pcm_t *pcm_handle, double(*generate_waveform)(double, Osc_t)){
  // Initialize waveform buffer
  double pd_buffer[SND_PCM_PERIOD_SIZE] = {0};

  // Create sound buffer
  for (int si_frame = 0; si_frame < SND_PCM_PERIOD_SIZE; si_frame++){
    gd_time = gd_time + gd_time_elapsed;
    if (gd_freq > 1.0){
      pd_buffer[si_frame] = generate_waveform(gd_time, ge_oscillator);
    }
  }

  // Write PCM buffer
  return snd_pcm_writei(pcm_handle, pd_buffer, SND_PCM_PERIOD_SIZE);
}


int audio_driver_close(snd_pcm_t *pcm_handle){
  // Close PCM
  return snd_pcm_close(pcm_handle);
}

int wiringPi_init(void){
    int si_return = wiringPiSetup();
    if (si_return){
      pinMode(PIN_KEY_C, INPUT);
      pinMode(PIN_KEY_D, INPUT);
      pinMode(PIN_KEY_E, INPUT);
      pinMode(PIN_KEY_F, INPUT);
      pinMode(PIN_KEY_G, INPUT);
      pinMode(PIN_KEY_A, INPUT);
      pinMode(PIN_OSC_MSB, INPUT);
      pinMode(PIN_OSC_LSB, INPUT);
    }
    return si_return;
}


void MeasurementsFunc(void){
  // Initialize wiringPi
  wiringPi_init();

  while(1){
    sem_wait(&gmx_measurements);
    // Select oscillator
    ge_oscillator = digitalRead(PIN_OSC_MSB)*2 + digitalRead(PIN_OSC_LSB);
            
    // Check key note
    if (digitalRead(PIN_KEY_C) == 1){
        gd_freq = FREQ_C;
    }
    if (digitalRead(PIN_KEY_D) == 1){
        gd_freq = FREQ_D;
    }
    if (digitalRead(PIN_KEY_E) == 1){
        gd_freq = FREQ_E;
    }
    if (digitalRead(PIN_KEY_F) == 1){
        gd_freq = FREQ_F;
    }
    if (digitalRead(PIN_KEY_G) == 1){
        gd_freq = FREQ_G;
    }
    if (digitalRead(PIN_KEY_A) == 1){
        gd_freq = FREQ_A;
     }
    
    gd_freq = 0.0;     
    sem_post(&gmx_measurements);
  }
}


void AudioDriverFunc(void){

  // PCM variables initialization
  snd_pcm_t *pcm_handle = audio_driver_init();

  while(1){
    // Write PCM buffer
    audio_driver_play(pcm_handle, oscillator);
   }
   // Close audio driver
   audio_driver_close(pcm_handle);
}


int main(void){


    // Time global variables 
    gd_time = 0.0;
    gd_time_elapsed = 1.0/((double)SND_PCM_RATE_STD);
    ge_oscillator = OSC_SINE;


    // Initialization frequency
    gd_freq = 0.0;


    // Initialize mutex
    sem_init(&gmx_measurements, 0, 1);

    // Threads definition
    pthread_t th_measurements;
    pthread_t th_audio_driver;

    // Create threads
    pthread_create(&th_measurements, 0, (void* (*)(void*)) MeasurementsFunc, NULL);
    pthread_create(&th_audio_driver, 0, (void* (*)(void*)) AudioDriverFunc, NULL);

    // Create threads
    pthread_join(th_measurements, NULL);
    pthread_join(th_audio_driver, NULL);

    return 0;
}

