/*
TUTORIAL ALSA 1: display PCM types and formats
From: https://www.linuxjournal.com/article/6735
*/
#include <alsa/asoundlib.h>

int main(void){
    printf("ALSA library version: %s\n", SND_LIB_VERSION_STR);

    printf("PCM stream types:\n");
    for (int val = 0; val <= SND_PCM_STREAM_LAST; val++){
        printf("\t%s\n", snd_pcm_stream_name( (snd_pcm_stream_t) val));
    }

    printf("PCM access types:\n");
    for (int val = 0; val <= SND_PCM_ACCESS_LAST; val++){
        printf("\t%s\n", snd_pcm_access_name( (snd_pcm_access_t) val));
    }

    printf("PCM formats:\n");
    for (int val = 0; val <= SND_PCM_FORMAT_LAST; val++){
        if (snd_pcm_format_name( (snd_pcm_format_t) val) != NULL){
            printf("\t%s (%s)\n", snd_pcm_format_name( (snd_pcm_format_t) val),
                                 snd_pcm_format_description((snd_pcm_format_t) val));
        }
    }

    printf("PCM sub-formats:\n");
    for (int val = 0; val <= SND_PCM_SUBFORMAT_LAST; val++){
        printf("\t%s (%s)\n", snd_pcm_subformat_name( (snd_pcm_subformat_t) val),
                              snd_pcm_subformat_description( (snd_pcm_subformat_t) val));
    }

    printf("PCM states:\n");
    for (int val = 0; val <= SND_PCM_STATE_LAST; val++){
        printf("\t%s\n", snd_pcm_state_name( (snd_pcm_state_t) val));
    }
    return 0;
}
