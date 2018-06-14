#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <wiringPi.h>
#include <math.h>
// No me convence que esta libreria sea del todo correcta. Probablemente
// por las variables FLAG_RISE y FLAG_FALL. 

// Funciones a realizar en las interrupciones
static int time_rise, time_fall, FLAG_RISE, FLAG_FALL;
void EchoRise (void) { time_rise = micros(); FLAG_RISE = 1;}
void EchoFall (void) { time_fall = micros(); FLAG_FALL = 1;}

// Interrupciones
void CreacionInterrupcionesDistancia (int ECHO_RISEpin, int ECHO_FALLpin) {
	// Creo las interrupciones
	wiringPiISR (ECHO_RISEpin, INT_EDGE_RISING, &EchoRise) ;
    wiringPiISR (ECHO_FALLpin, INT_EDGE_FALLING, &EchoFall) ;
}

//Medir la distancia
float Distancia(int TRIG_PIN){
	/* Esta función usa las interrupciones previamente creadas para medir
	*  la distancia. El sensor utilizado no es muy bueno, hay que medir 
	*  distancia a la pared para que funcionen bien, es incómodo pues 
	*  hay que ir moviendo la protoboard y la RPi.*/
	
	// Pongo a 0 el trigger, no envío ultrasonido
	digitalWrite (TRIG_PIN, 0);
	delayMicroseconds(20);
	
	// Envio un pulso
	digitalWrite (TRIG_PIN, 1);
	delayMicroseconds(20);
	digitalWrite (TRIG_PIN, 0);
	
	// Variables a 0
	FLAG_RISE = 0; FLAG_FALL = 0;
	
	int time_high = 0, count = 0;
	
	// Mido la distancia 
	int t_ref = micros(); 
	while ( count < 3) {
		if ( (micros() - t_ref) > 6000)
			count = 3;
			
		if ((FLAG_RISE == 0) && (FLAG_FALL == 0) && (count == 0))
			count++;
		if ( (FLAG_RISE == 1) && (FLAG_FALL == 0) && (count == 1))
			count++;
		if( (FLAG_RISE == 1) && (FLAG_FALL == 1) ){
			time_high = time_fall - time_rise;
			count++;			
		}
	}
	return 340.0*time_high/20000.0;
}

int GenerarNota(int distancia){
	// Se devuelve una nota distinta cada 5cm.
	int distEff = (int) (distancia/5); 
	int nota;
	switch (distEff){
		case 0: // < 5 cm
			nota = 0;
			break;
		case 1: // 5-10 cm
			nota = 262;
			break;
		case 2: // 10-15 cm
			nota = 277;
			break;
		case 3: // 10-15 cm
			nota = 294;
			break;
		case 4: // 20-25 cm
			nota = 330;
			break;
		case 5: // 25-30 cm
			nota = 350;
			break;
		case 6: // 30-35 cm
			nota = 370;
			break;
		case 7: // 35-40 cm
			nota = 392;
			break;
		case 8: // 40-45 cm
			nota = 415;
			break;
		case 9: // 45-50 cm
			nota = 440;
			break;
		case 10: // 50-55 cm
			nota = 466;
			break;
		case 11: // 55-60 cm
			nota = 493;
			break;
		case 12: // 65-70 cm
			nota = 523;
			break;
		default: // >70 cm
			nota = 0;
			break;
		
	}
	return nota;
}


