#include <alsa/asoundlib.h>
#include <math.h>
#define SND_PCM_PERIOD_SIZE (4)
#define SND_PCM_CHANNEL_MONO (1)
#define SND_PCM_CHANNEL_STEREO 2)
#define SND_PCM_RATE_STD (44100)
#define SND_PCM_SOFT_RESAMPLE (1)
#define SND_PCM_LATENCY (500000)

typedef enum {
    OSC_SINE,
    OSC_SQUARE,
    OSC_TRIANGLE,
    OSC_SAW_ANA,
    OSC_SAW_DIG,
    OSC_NOISE
} Osc_t;


float oscillator(float f_freq, float f_time, Osc_t e_type) {
    /* OSCILLATOR returns the the amplitude of the specified oscillator e_type
    at a given moment given its frequency.*/

    // Initialization
    float d_output = 0.0;

    // Frequency oscillation times time
    float f_W_T = f_freq * 2.0 * M_PI * f_time; 

    // Oscillator definitions
    switch (e_type) {
    case OSC_SINE:
        d_output = sin(f_W_T);
        break;

    case OSC_SQUARE:
        d_output = sin(f_W_T) > 0 ? 1.0 : -1.0;
        break;

    case OSC_TRIANGLE:
        d_output = asin(sin(f_W_T)) * M_2_PI;
        break;

    case OSC_SAW_ANA:  // summation of Fourier harmonics
        d_output = 0.0;

        for (int n = 1; n < 50; n++)  // 50 armonics are used by default
            d_output += (sin(n * f_freq * 2.0 * M_PI * f_time)) / ((float) n);

        d_output = d_output * M_2_PI;
        break;

    case OSC_SAW_DIG:  // computation of sawtooth signal arithmetically
        d_output = M_2_PI * (f_freq * M_PI * fmod(f_time, 1.0 / f_freq) - M_PI_2);
        break;

    case OSC_NOISE: 
        d_output = 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
        break;

    default:
        d_output = 0.0;
    }

    return d_output;
}


int main(void){
	
    // Initialization
    int si_error = 0;
    snd_pcm_t *pcm_handle = NULL;
	pcm_handle = (snd_pcm_t *)malloc(sizeof(snd_pcm_t*));
    float f_buffer [SND_PCM_PERIOD_SIZE];
	const float f_time_elapsed = 1.0/((float)SND_PCM_RATE_STD);
	float f_time = 0.0;
	
    // Open device
    si_error = snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (si_error < 0){
            printf("Playback open error: %s\n", snd_strerror(si_error));
            exit(EXIT_FAILURE);
    }

    // Set software and hardware parameters    
    si_error = snd_pcm_set_params(pcm_handle,
                                  SND_PCM_FORMAT_FLOAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  SND_PCM_CHANNEL_MONO,
                                  SND_PCM_RATE_STD,
                                  SND_PCM_SOFT_RESAMPLE,
                                  SND_PCM_LATENCY);
	
	if (si_error < 0){
		printf("Playback open error: %s\n", snd_strerror(si_error));
		exit(EXIT_FAILURE);
	}
    

    // Generate and play sounds
    while(1){

        for (int si_frame = 0; si_frame < SND_PCM_PERIOD_SIZE; si_frame++){
            f_time = f_time + f_time_elapsed;
            f_buffer[si_frame] = oscillator(440.0, f_time, OSC_SINE);
        }

        snd_pcm_writei(pcm_handle, f_buffer, SND_PCM_PERIOD_SIZE);
    }

    snd_pcm_close(pcm_handle);
    return 0;
}
