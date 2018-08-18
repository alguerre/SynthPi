#define ALSA_PCM_NEW_HW_PARAMS_AP
#include <string.h>
#include <alsa/asoundlib.h>
#define FIVE_SECONDS 5000000

int main(void){
    int si_error = 0;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *hw_params = NULL;
    unsigned int ui_rate = 44100;
    unsigned int ui_channels = 2;
    unsigned int ui_period_time = 0;
    snd_pcm_uframes_t st_frames = 32;
    char *pc_buffer = NULL;
    int si_size = 0;
    int si_iterations = 0;

    // Open PCM device for playback
    si_error = snd_pcm_open(
            &pcm_handle,  /* Returned PCM handle, snd_pcm_t ** */
            "default", /* ASCII identifier of the PCM handle*/
            SND_PCM_STREAM_PLAYBACK, /* Wanted stream, PLAYBACK or CAPTURE */
            0 /* Open mode */
        );

    if (si_error < 0){
        fprintf(stderr, "Unable to open pcm device: %s\n", snd_strerror(si_error));
        exit(1);
    }

    // Allocate a hardware parameters object
    snd_pcm_hw_params_malloc(&hw_params);  /* This is a define*/

    // Fill params with default values from pcm
    snd_pcm_hw_params_any(
        pcm_handle, /* PCM handle */
        hw_params  /* Hardware configuration parameters */
    );

    // Set the desired hardware parameters: 
    snd_pcm_hw_params_set_access( /* Restrict a configuration space to contain only one access type*/
        pcm_handle, 
        hw_params,
        SND_PCM_ACCESS_RW_INTERLEAVED /* snd_pcm_access_t is an enumerate, interlieved mode is selected */
    );
    snd_pcm_hw_params_set_format(
        pcm_handle,
        hw_params,
        SND_PCM_FORMAT_S16_LE
    );
    snd_pcm_hw_params_set_channels(
        pcm_handle, 
        hw_params,
        ui_channels);

    snd_pcm_hw_params_set_rate_near(
        pcm_handle, 
        hw_params,
        &ui_rate, /* Approximate target rate, return the actual value through this pointer */
        NULL  /* Sub unit direction */
    );

    // Write new parameters to the driver
    si_error = snd_pcm_hw_params(pcm_handle, hw_params);
    if (si_error < 0){
        fprintf(stderr, "Unable to set hw parameters: %s\n", snd_strerror(si_error));
        exit(1);
    }

    // Use a buffer large enough to hold one period
    snd_pcm_hw_params_get_period_size(hw_params, &st_frames, NULL);
    si_size = st_frames * 2 * 2;  // 2 bytes/sample, 2 channels
    pc_buffer = (char *) malloc(si_size);

    // Compute number of iterations to produce 5s of audio
    snd_pcm_hw_params_get_period_time(hw_params, &ui_period_time, NULL);
    si_iterations = FIVE_SECONDS/ui_period_time;    
    printf("period time = %d\n", ui_period_time);
    printf("iterations  = %d\n", si_iterations);
    printf("frames = %ld\n", st_frames);

    // Produce sound
    for (int i = 0; i < si_iterations; i++){
        // Read input data
        si_error = read(0, pc_buffer, si_size);
        if (si_error == 0){
            fprintf(stderr, "End of file on input.\n");
        } 
        else if (si_error < 0){
            fprintf(stderr, "short read: read %d bytes\n", si_error);
        }

        // Write interleaved frames to a PCM
        si_error = snd_pcm_writei(pcm_handle, pc_buffer, st_frames);
        if (si_error == -EPIPE){
            fprintf(stderr, "Underrun occurred\n");
            snd_pcm_prepare(pcm_handle);
        }
        else if (si_error < 0){
            fprintf(stderr, "Error from writei: %s\n", snd_strerror(si_error));
        }
        else if ( (long) si_error != st_frames){
            fprintf(stderr, "short write, write %d frames\n", si_error);
        }
    }
    
    snd_pcm_drain(pcm_handle);  // Stop PCM (preserving pending frames)
    snd_pcm_close(pcm_handle);  // Close PCM handle
    return 0;
}

