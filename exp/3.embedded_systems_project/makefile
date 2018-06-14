CC = gcc
CFLAGS = -Wall -g

all: DistSound.o DistSoundLib.o DistSoundLib.h bateriaLib.o bateriaLib.h matrizLED.o matrizLED.h
	gcc $(CFLAGS) -o DistSound_exe DistSoundLib.o DistSound.o bateriaLib.o matrizLED.o -lwiringPi -lm -lSDL -lSDL_mixer

clean:
	-rm *.o
