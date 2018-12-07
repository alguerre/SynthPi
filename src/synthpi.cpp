/* DESCRIPTION todo */
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

#include "wiringPi.h"
#include "measurements.h"
#include "audio_driver.h"

// Global variables definition
Measurements ob_measurements;
Meas_t st_measurements;
sem_t mx_measurements;
bool b_exit = false;


bool Exit() {
  /* EXIT is used to finish the execution of the synthesizer. */
  if ((digitalRead(pk_keys[0]) == HIGH) && 
    (digitalRead(pk_keys[k_n_keys-1]) == HIGH))
    return true;

  return false;
}


void AudioDriverFunc() {
  /* AUDIODRIVERFUNC launches the audio driver to play sounds. */
  while (b_exit == false) {
    std::cout << "hola" << std::endl;
    delay(1000);
  }
}


void MeasurementsFunc() {
  /* MEASUREMENTSFUNC execute all the capabilities related with measurements 
   * from external devices which are used as configuration. */
  while (b_exit == false) {
    sem_wait(&mx_measurements);
    st_measurements = ob_measurements.GetMeasurements();
    ob_measurements.Print();
    sem_post(&mx_measurements);
    b_exit = Exit();
    delay(1000);
  }
  
}


void ConfigureWiringPi() {
  /* CONFIGUREWIRINGPI setups and initializes the wiringPi utilities. */
  wiringPiSetup();
  for (int i = 0; i < k_n_keys; i++) {
    pinMode(pk_keys[i], INPUT);
  }
}


int main(void){

  // Initialize mutex
  sem_init(&mx_measurements, 0, 1);

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

