#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define MATRIX_ADR 0x70
#define MATRIX_START 0x21 // enciende el oscilador
#define MATRIX_BLINK 0x81 // 0x83, 0x85, 0x87 = parpadeo a distintas frecuencias
#define MATRIX_BRIGHTNESS 0xE0 // 0xE0, 0xE2,..., 0xEA,... = intensidad de brillo

int matrizSetup(void){
	int fd = wiringPiI2CSetup ( MATRIX_ADR );
	wiringPiI2CWrite(fd, MATRIX_START);
	wiringPiI2CWrite(fd, MATRIX_BLINK);
	wiringPiI2CWrite(fd, MATRIX_BRIGHTNESS);
	return fd;
}

void encenderTodo(int fd){
	wiringPiI2CWriteReg8(fd, 0x00, 0xFF);
	wiringPiI2CWriteReg8(fd, 0x02, 0xFF);
	wiringPiI2CWriteReg8(fd, 0x04, 0xFF);
	wiringPiI2CWriteReg8(fd, 0x06, 0xFF);
	wiringPiI2CWriteReg8(fd, 0x08, 0xFF);
	wiringPiI2CWriteReg8(fd, 0x0A, 0xFF);
	wiringPiI2CWriteReg8(fd, 0x0C, 0xFF);
	wiringPiI2CWriteReg8(fd, 0x0E, 0xFF);
}

void apagarTodo(int fd){
	wiringPiI2CWriteReg8(fd, 0x00, 0x00);
	wiringPiI2CWriteReg8(fd, 0x02, 0x00);
	wiringPiI2CWriteReg8(fd, 0x04, 0x00);
	wiringPiI2CWriteReg8(fd, 0x06, 0x00);
	wiringPiI2CWriteReg8(fd, 0x08, 0x00);
	wiringPiI2CWriteReg8(fd, 0x0A, 0x00);
	wiringPiI2CWriteReg8(fd, 0x0C, 0x00);
	wiringPiI2CWriteReg8(fd, 0x0E, 0x00);
}

void iluminaNotas(int notas[8], int fd){
	int columna[8] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E};
	int i;
	for (i = 0; i < 8; i++){
		if ( notas[i] == 262 ){
			wiringPiI2CWriteReg8(fd, columna[i], 0b01000000);}
		if ( notas[i] == 277 )
			wiringPiI2CWriteReg8(fd, columna[i], 0b01000000);
		if ( notas[i] == 294 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01100000);
		if ( notas[i] == 330 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01110000);
		if ( notas[i] == 350 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01111000);
		if ( notas[i] == 370 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01111000);
		if ( notas[i] == 392 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01111100);
		if ( notas[i] == 415 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01111100);
		if ( notas[i] == 440 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01111110);
		if ( notas[i] == 466 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01111110);
		if ( notas[i] == 493 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b01111111);
		if ( notas[i] == 523 ) 
			wiringPiI2CWriteReg8(fd, columna[i], 0b11111111);
	}
}
