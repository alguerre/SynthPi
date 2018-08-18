#include <alsa/asoundlib.h>
#include <math.h>
#define BUFFER_LEN 48000
#define RATE 44100
#define FREQ 440.0


int main(void){
    // Initialization
    int si_error = 0;
    snd_pcm_t *pcm_handle;
    float d_buffer [BUFFER_LEN*3];

    // Open device
    si_error = snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (si_error < 0){
            printf("Playback open error: %s\n", snd_strerror(si_error));
            exit(EXIT_FAILURE);
    }

    // Set software and hardware parameters    
    si_error = snd_pcm_set_params(pcm_handle, /* pcm handle */
                                  SND_PCM_FORMAT_FLOAT, /* format */
                                  SND_PCM_ACCESS_RW_INTERLEAVED, /* access */
                                  1, /* channels */
                                  RATE, /* rate */
                                  1, /* soft resample (0=disallow, 1 = allow)*/
                                  500000); /* latency in us*/
    if (si_error < 0){   
            printf("Playback open error: %s\n", snd_strerror(si_error));
            exit(EXIT_FAILURE);
    }

    // Generate sine wave
    printf("Sine tone at %f Hz\n", FREQ);
    for (int k = 0; k < BUFFER_LEN; k++){
        d_buffer[k] = sin(2*M_PI*k*FREQ/RATE);  // sine wave value generation         
    }       
    for (int k = BUFFER_LEN; k < BUFFER_LEN*2; k++){
        d_buffer[k] = sin(2*M_PI*k*2*FREQ/RATE);  // sine wave value generation         
    }       
    for (int k = BUFFER_LEN*2; k < BUFFER_LEN*3; k++){
        d_buffer[k] = sin(2*M_PI*k*3*FREQ/RATE);  // sine wave value generation         
    }
       
    // Write PCM
    for (int j = 0; j < 5; j++){
        snd_pcm_writei(pcm_handle, d_buffer, 3*BUFFER_LEN);  // sending values to sound driver
    }

    snd_pcm_close(pcm_handle);
    return 0;
}
