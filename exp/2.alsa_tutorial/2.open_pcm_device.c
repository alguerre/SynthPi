#define ALSA_PCM_NEW_HW_PARAMS_AP
#include <alsa/asoundlib.h>

int main(void){
    int si_error;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *hw_params;
    unsigned int ui_rate = 44100;
    unsigned int ui_channels = 2;
    unsigned int ui_period_time;
    snd_pcm_access_t st_access;
    snd_pcm_format_t st_format;
    snd_pcm_subformat_t st_subformat;
    snd_pcm_uframes_t st_frames;
    unsigned int ui_buffer_time;
    unsigned int ui_buffer_periods;
    unsigned int ui_rate_num;
    unsigned int ui_rate_den;

    // Open PCM device for playback
    si_error = snd_pcm_open(
            &pcm_handle,  /* Returned PCM handle, snd_pcm_t ** */
            "default", /* ASCII identifier of the PCM handle*/
            SND_PCM_STREAM_PLAYBACK, /* Wanted stream, PLAYBACK or CAPTURE */
            0 /* Open mode */
        );

    if (si_error < 0){
        printf("Unable to open pcm device: %s\n", snd_strerror(si_error));
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
        printf("Unable to set hw parameters: %s\n", snd_strerror(si_error));
        exit(1);
    }


    // Display information about the PCM interface
    printf("PCM handle name = %s\n", snd_pcm_name(pcm_handle));
    printf("PCM state = %s\n", snd_pcm_state_name(snd_pcm_state(pcm_handle)));
   
    snd_pcm_hw_params_get_access(hw_params, &st_access);
    printf("access type = %s\n", snd_pcm_access_name(st_access));

    snd_pcm_hw_params_get_format(hw_params, &st_format);
    printf("format = %s\n", snd_pcm_format_name(st_format));

    snd_pcm_hw_params_get_subformat(hw_params, &st_subformat);
    printf("subformat = %s (%s)\n", snd_pcm_subformat_name(st_subformat),
                                    snd_pcm_subformat_description(st_subformat));    

    snd_pcm_hw_params_get_channels(hw_params, &ui_channels);
    printf("channels = %d\n", ui_channels);

    snd_pcm_hw_params_get_rate(hw_params, &ui_rate, NULL);
    printf("rate = %d bps\n", ui_rate);

    snd_pcm_hw_params_get_period_time(hw_params, &ui_period_time, NULL);
    printf("period time = %d us\n", ui_period_time);

    snd_pcm_hw_params_get_period_size(hw_params, &st_frames, NULL);
    printf("period size = %ld frames\n", st_frames);

    snd_pcm_hw_params_get_buffer_time(hw_params, &ui_buffer_time, NULL);
    printf("buffer time = %d us\n", ui_buffer_time);

    snd_pcm_hw_params_get_buffer_size(hw_params, &st_frames);
    printf("buffer size = %ld frames\n", st_frames);

    snd_pcm_hw_params_get_periods(hw_params, &ui_buffer_periods, NULL);
    printf("periods per buffer = %d frames\n", ui_buffer_periods);

    snd_pcm_hw_params_get_rate_numden(hw_params, &ui_rate_num, &ui_rate_den);
    printf("exact rate = %d/%d bps\n", ui_rate_num, ui_rate_den);

    printf("is batch = %d\n", snd_pcm_hw_params_is_batch(hw_params));
    
    printf("is block transfer = %d\n", snd_pcm_hw_params_is_block_transfer(hw_params));
    
    printf("is double = %d\n", snd_pcm_hw_params_is_double(hw_params));
    
    printf("is half duplex = %d\n", snd_pcm_hw_params_is_half_duplex(hw_params));
    
    printf("is joint duplex = %d\n", snd_pcm_hw_params_is_joint_duplex(hw_params));
    
    printf("can overrange = %d\n", snd_pcm_hw_params_can_overrange(hw_params));
    
    printf("can mmap = %d\n", snd_pcm_hw_params_can_mmap_sample_resolution(hw_params));
    
    printf("can pause = %d\n", snd_pcm_hw_params_can_pause(hw_params));
    
    printf("can resume = %d\n", snd_pcm_hw_params_can_resume(hw_params));
    
    printf("can sync start = %d\n", snd_pcm_hw_params_can_sync_start(hw_params));
    
    snd_pcm_close(pcm_handle);

    return 0;
}

