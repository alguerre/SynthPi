#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "DistSoundLib.h"
#include "bateriaLib.h"
#include "matrizLED.h"

#define TRIG 0 // envia el ultrasonido
#define ECHO_RISE 1 // recepcion del ultrasonido
#define ECHO_FALL 2 // recepcion del ultrasonido

#define BUTTON_PIN_ONE 22 // bateria
#define BUTTON_PIN_TWO 23 // bateria
#define BUTTON_PIN_THREE 24 // bateria
#define TIMBRE_PIN 25 // para la seleccion del timbre
#define OFF_BUTTON 26 // para parar la ejecucion

static int NOTA = 0;
static int NOTA_PREV = 0;
static int TIMBRE = 0;
static int BREAK = 0; // se utiliza para parar el programa

void timbreInt(void){ // función para la interrupción del pin TIMBRE_PIN
	TIMBRE++;
	TIMBRE = TIMBRE%6;
}

void apagar(void){ // función para la interrupción del pin OFF_BUTTON
	BREAK++;
}

PI_THREAD (SoundGenerator){
	/* Este hilo se utiliza para cargar y generar los sonidos. Se tienen
	 * sonidos con 6 timbres distintos y 12 notas para cada timbre. Se-
	 * gún la variable NOTA se reproducirá uno u otro sonido. */
	 
	// Sonidos
	char *sine[12] = {"notas/sine262.wav", "notas/sine277.wav", 
		"notas/sine294.wav", "notas/sine330.wav", "notas/sine350.wav",
		"notas/sine370.wav", "notas/sine392.wav", "notas/sine415.wav",
		"notas/sine440.wav", "notas/sine466.wav", "notas/sine493.wav",
		"notas/sine523.wav"};
	char *square[12] = {"notas/square262.wav", "notas/square277.wav", 
		"notas/square294.wav", "notas/square330.wav", "notas/square350.wav",
		"notas/square370.wav", "notas/square392.wav", "notas/square415.wav",
		"notas/square440.wav", "notas/square466.wav", "notas/square493.wav",
		"notas/square523.wav" };
	char *triang[12] = {"notas/triang262.wav", "notas/triang277.wav", 
		"notas/triang294.wav", "notas/triang330.wav", "notas/triang350.wav",
		"notas/triang370.wav", "notas/triang392.wav", "notas/triang415.wav",
		"notas/triang440.wav", "notas/triang466.wav", "notas/triang493.wav",
		"notas/triang523.wav"  };
	char *sawtooth[12] = {"notas/sawtooth262.wav", "notas/sawtooth277.wav", 
		"notas/sawtooth294.wav", "notas/sawtooth330.wav", "notas/sawtooth350.wav",
		"notas/sawtooth370.wav", "notas/sawtooth392.wav", "notas/sawtooth415.wav",
		"notas/sawtooth440.wav", "notas/sawtooth466.wav", "notas/sawtooth493.wav",
		"notas/sawtooth523.wav" };
	char *customOne[12] = {"notas/customOne262.wav", "notas/customOne277.wav", 
		"notas/customOne294.wav", "notas/customOne330.wav", "notas/customOne350.wav",
		"notas/customOne370.wav", "notas/customOne392.wav", "notas/customOne415.wav",
		"notas/customOne440.wav", "notas/customOne466.wav", "notas/customOne493.wav",
		"notas/customOne523.wav" };
	char *customTwo[12] = {"notas/customTwo262.wav", "notas/customTwo277.wav", 
		"notas/customTwo294.wav", "notas/customTwo330.wav", "notas/customTwo350.wav",
		"notas/customTwo370.wav", "notas/customTwo392.wav", "notas/customTwo415.wav",
		"notas/customTwo440.wav", "notas/customTwo466.wav", "notas/customTwo493.wav",
		"notas/customTwo523.wav"  };
	
	// Matriz de sonidos
	Mix_Chunk *sound[6][12];
	
	// Cargo los wav en el array sounds[i][j] y doy volumen
	int i, j;
	for (i = 0; i < 6; i++){
		for (j = 0; j < 12; j++){
			if (i == 0)
				sound[i][j] = Mix_LoadWAV(sine[j]);
			if (i == 1)
				sound[i][j] = Mix_LoadWAV(square[j]);
			if (i == 2)
				sound[i][j] = Mix_LoadWAV(triang[j]);
			if (i == 3)
				sound[i][j] = Mix_LoadWAV(sawtooth[j]);
			if (i == 4)
				sound[i][j] = Mix_LoadWAV(customOne[j]);
			if (i == 5)
				sound[i][j] = Mix_LoadWAV(customTwo[j]);
			Mix_VolumeChunk(sound[i][j], 50);
		}
	}
	
	// Reproduzco el sonido correspondiente a la variable NOTA. Si no se
	// produce ningún cambio de nota no ceso la reproducción.
	int channel;			
	int notaList[12] = {262, 277, 294, 330, 350, 370, 392,415, 440, 466, 493, 523};
	int pos, k;
	for(;;){
		if (NOTA == NOTA_PREV){
		}
		else{
			Mix_HaltChannel(channel); // si la nota es distinta a la anterior paro el canal
			if (NOTA != 0){
				for (k = 0; k < 12; k++){
					if (NOTA == notaList[k]){
						pos = k; 
						break;
					}
				}
			
				channel = Mix_PlayChannel(-1, sound[TIMBRE][pos], 0);			
				while( (Mix_Playing(channel) != 0) && (NOTA != NOTA_PREV) ){ }
			}
							
		}
	}
	
}


PI_THREAD (LEDSandDRUMS){
	/* Este hilo se encarga de encender la matriz de LEDS. 
	 * Cuando suena la batería se enciende entera. El resto del tiempo
	 * se enciende según el vector NOTA_LED. También produce los sonidos
	 * de la bateria al pulsar los botones destinados a ello. */
	 
	// Creo interrupciones para la bateria
	interrupcionesBateria(BUTTON_PIN_ONE, BUTTON_PIN_TWO, BUTTON_PIN_THREE);
	int HIT = 0; // para encender los LEDS al darle a la batería
	int NOTA_LED[8] = {0,0,0,0,0,0,0,0};
	int shift = 0;	// para el bucle que actualiza NOTA_LED
	int fd = matrizSetup();
	apagarTodo(fd);
	
	for(;;){
		HIT = bateria(); 
		if (HIT == 1){
			encenderTodo(fd);
			delay(100);
			HIT = 0;
			apagarTodo(fd);
		}
		else{
			iluminaNotas( NOTA_LED, fd);
		}
		
		// Actualizo el vector NOTA_LED
		if ( (NOTA != NOTA_PREV) ){
			for (shift = 7; shift > 0; shift--){
				NOTA_LED[shift] = NOTA_LED[shift-1];
			}		
			NOTA_LED[0] = NOTA;
		}	
		
		delay(50); // cada 50ms actualizo la matriz
	}

}

int main(void){
	// Cargo wiringPi
	wiringPiSetup();	
	
	// Cargo SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	 
	// Cargo SDL_mixer
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;	 
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}
	
	
	// Creo el hilo
	piThreadCreate (SoundGenerator);
	piThreadCreate (LEDSandDRUMS);
	
	// Interrupcion para el timbre
	wiringPiISR (TIMBRE_PIN, INT_EDGE_RISING, &timbreInt) ;
	wiringPiISR (OFF_BUTTON, INT_EDGE_RISING, &apagar);
	
	// Inicializo los pines de lectura/escritura
	/*pinMode (TRIG, OUTPUT);
	pinMode (ECHO_FALL, INPUT);
	pinMode (ECHO_RISE, INPUT);*/
	
	// Creo las interrupciones
	CreacionInterrupcionesDistancia ( ECHO_RISE, ECHO_FALL);
    		
    // Pongo a 0 el trigger, no envío ultrasonido
	digitalWrite (TRIG, 0);

	

	float dist = 0; // distancia
	
	for(;;){
		// Mido distancia y asigno una nota. 
		dist = Distancia(TRIG);	
		NOTA_PREV = NOTA; // Actualizo la nota anterior
		NOTA = GenerarNota(dist);
		
		// Si BREAK > 0 paro el bucle
		if (BREAK > 0) break;
		
		delay(50); // paro 50ms, no hace falta emitir sonidos continuamente


	}
	
	return 0;
}
