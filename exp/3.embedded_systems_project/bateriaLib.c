#include <stdio.h>
#include <wiringPi.h>

// Cada valor de 'instrument' hace referencia a un instrumento
static int instrument; // realmente es necesario que esta variable sea global??

void instrument1(void){
	instrument = 1;
}

void instrument2(void){
	instrument = 2;
}
void instrument3(void){
	instrument = 3;
}

void interrupcionesBateria(int PinOne, int PinTwo, int PinThree){
	// Establezco las interrupciones
	if( wiringPiISR (PinOne, INT_EDGE_RISING, &instrument1) < 0){
		printf("Imposible crear la interrupción para instrument1\n");
	}
	if( wiringPiISR (PinTwo, INT_EDGE_RISING, &instrument2) < 0){
		printf("Imposible crear la interrupción para instrument2\n");
	}
	if( wiringPiISR (PinThree, INT_EDGE_RISING, &instrument3) < 0){
		printf("Imposible crear la interrupción para instrument3\n");
	}
		
}

int bateria(void){ 
	// Se produce un sonido de batería dependiende del valor de instrument.
	int hit = 0;
	switch( instrument ){
		case 0:
			break;
		case 1: 
			system("aplay -q /home/pi/Desktop/proyecto/sonidos/palmada2.wav");
			hit = 1;
			break;
		case 2:
			system("aplay -q /home/pi/Desktop/proyecto/sonidos/pop.wav");
			hit = 1;
			break;
		case 3:
			system("aplay -q /home/pi/Desktop/proyecto/sonidos/caja.wav");
			hit = 1;
			break;
		default:
			hit = 0;
			break;
	}		
	instrument = 0;
	return hit;
		
}
