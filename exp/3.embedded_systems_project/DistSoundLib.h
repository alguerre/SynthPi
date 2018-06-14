#ifndef _DISTSOUNDLIB_H
#define _DISTSOUNDLIB_H

void EchoRise (void);
void EchoFall (void);
void CreacionInterrupcionesDistancia (int ECHO_RISEpin, int ECHO_FALLpin);
float Distancia(int TRIGpin);
int GenerarNota(int distancia);

#endif
