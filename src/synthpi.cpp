/* DESCRIPTION todo */
#include <iostream>
//#include <pthread.h>
//#include <semaphore.h>
#include "types.h"
#include "wiringPi.h"
//#include "measurements.h"
#include "audio_driver.h"
#include "oscillator.h"

#define FREQ_C 261.626
#define FREQ_D 293.664
#define FREQ_E 329.628
#define FREQ_F 349.228
#define FREQ_G 391.996
#define FREQ_A 440.000

float pf_notes[6] = {FREQ_C, FREQ_D, FREQ_E, FREQ_F, FREQ_G, FREQ_A};

// Global variables definition
//Measurements gob_measurements;
//Meas_t gst_measurements;
//sem_t gmx_measurements;
bool gb_exit = false;


// Global varialbes definition
double gf_freq = 0.0;
Osc_t ge_oscillator = OSC_SINE;


float sound_generator(float f_time){
  /* SOUND_GENERATOR produce the waveform value. It is called by audio_driver
   * to generate the complete waveform and play it. */
  float f_mixed_output = 0.0;
  f_mixed_output = oscillator(gf_freq, f_time, ge_oscillator, 0.0, 0.0);

  return f_mixed_output;
}


//void MeasurementsFunc() {
  /* MEASUREMENTSFUNC execute all the capabilities related with measurements
   * from external devices which are used as configuration. */
/*  while ( !gb_exit ) {
    sem_wait(&gmx_measurements);
    //st_measurements = ob_measurements.GetMeasurements();

    // Simulated measurements
    gst_measurements.si_volume = k_si_adc_max/2;
    gst_measurements.pe_oscillator[0] = OSC_SINE;
    gst_measurements.pe_oscillator[1] = OSC_NONE;
    gst_measurements.psi_octave[0] = 1;
    gst_measurements.psi_octave[1] = 1;
    gst_measurements.si_lfo = 0;
    gst_measurements.si_attack_time = 0;
    gst_measurements.si_decay_time = 0;
    gst_measurements.si_sustain_level = 0;
    gst_measurements.si_release_time = 0;

    sem_post(&gmx_measurements);

    delay(200);
  }

}
*/

void ConfigureWiringPi() {
  /* CONFIGUREWIRINGPI setups and initializes the wiringPi utilities. */
  wiringPiSetup();

  // Set input mode for keys
  for (int i = 0; i < k_si_n_keys; i++) {
    pinMode(k_psi_keys[i], INPUT);
  }

  // Set input keys for oscillator selection
  for (int i = 0; i < k_si_n_oscillators; i++) {
    pinMode(k_psi_gpio_oscillator_m[i], INPUT);
    pinMode(k_psi_gpio_oscillator_l[i], INPUT);
  }
}


int main(void){

  // Initialize audio driver
  AudioDriver *ob_audiodriver = NULL;
  ob_audiodriver = new AudioDriver;
  ob_audiodriver->ConfigureAlsa();

  // Initialize wiringPi
  ConfigureWiringPi();

  // Generate and play sounds
  while(1){
      // Select oscillator
      ge_oscillator = static_cast<Osc_t> (
          digitalRead(k_psi_gpio_oscillator_m[0])*2 +
          digitalRead(k_psi_gpio_oscillator_l[0])
          );

      // Check key note
      for (int i = 0; i < k_si_n_keys; i++){
        if (digitalRead(k_psi_keys[i]) == 1){
          gf_freq = pf_notes[i];
        }
      }

      // Write PCM buffer
      ob_audiodriver->PlaySound(sound_generator);

      gf_freq = 0.0;
  }

  return 0;
}

