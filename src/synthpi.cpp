/* SYNTHPI is a synthesizer for a Raspberry Pi board. Sound generation is
 * software based, external electronics is used for input and sound
 * configuration control.
 *
 * Author: Alonso Guerrero Llorente
 * E-mail: alguerre@outlook.com
 *
 */
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include "types.h"
#include "wiringPi.h"
#include "measurements.h"
#include "configuration.h"
#include "audio_driver.h"
#include "oscillator.h"

// Global variables definition
Config_t gst_configuration;
sem_t gmx_configuration;
bool gb_exit = false;
Oscillator gob_oscillator1;

// Global variables definition
double gf_freq = 0.0;
Osc_t ge_oscillator = OSC_SINE;


float SoundGenerator(float f_time){
  /* SOUNDGENERATOR produce the waveform value. It is called by audio_driver
   * to generate the complete waveform and play it. */
  float f_mixed_output = 0.0;
  float f_volume = 1.0;

  sem_wait(&gmx_configuration);
  f_volume = gst_configuration.f_volume;
  sem_post(&gmx_configuration);

  f_mixed_output = f_volume *
      gob_oscillator1.GenerateOscillation(gf_freq, f_time, gst_configuration, 0);


  return f_mixed_output;
}


void MeasurementsFunc() {
  /* MEASUREMENTSFUNC execute all the capabilities related with measurements
   * from external devices which are used as configuration. */

  // Object initialization
  Measurements gob_measurements;
  Configuration gob_configuration;
  Meas_t gst_measurements;

  // Measurements acquisition and processing
  while ( !gb_exit ) {
    sem_wait(&gmx_configuration);

    gst_measurements = gob_measurements.GetMeasurements();
    gst_configuration = gob_configuration.GetConfiguration(gst_measurements);
    //std::cout << gob_measurements << std::endl;
    //std::cout << gob_configuration << std::endl;
    sem_post(&gmx_configuration);

    delay(10);  // avoid port saturation
  }
}


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


void SoundFunc(void){
  /* SOUNDFUNC read the keyboard, generate waveform and play it in a dedicated
   * thread. */

  // Initialize wiringPi
  ConfigureWiringPi();

  // Initialize audio driver
  AudioDriver *ob_audiodriver = NULL;
  ob_audiodriver = new AudioDriver;
  ob_audiodriver->ConfigureAlsa();

  // Generate and play sounds
  while(!gb_exit){

      // Check key note
      for (int i = 0; i < k_si_n_keys; i++){
        if (digitalRead(k_psi_keys[i]) == 1){
          gf_freq = k_f_base_freq * pow(k_f_freq_note_interval, i);
        }
      }

      // Write PCM buffer
      ob_audiodriver->PlaySound(SoundGenerator);

      gf_freq = 0.0;
  }
}

int main(void){

  // Initialize mutex
  sem_init(&gmx_configuration, 0, 1);

  // Threads definition
  pthread_t th_measurements;
  pthread_t th_sound;

  // Create threads
  pthread_create(&th_measurements, 0, (void* (*)(void*)) MeasurementsFunc, NULL);
  pthread_create(&th_sound, 0, (void* (*)(void*)) SoundFunc, NULL);

  // Create threads
  pthread_join(th_measurements, NULL);
  pthread_join(th_sound, NULL);

  return 0;
}

