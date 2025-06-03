#ifndef MANEJOCADENAS_H_INCLUDED
#define MANEJOCADENAS_H_INCLUDED

#include "globales.h"
#include "mCtype.h"
#include "menu.h"
#include "jugar.h"
#include <stdio.h>

char pedirOpcion(const char *opciones, const char *validas);

void pedirNombre(char *nombreJugador, unsigned tamNombreJugador);

void convertirUnsignedCharACadena(void *numero, char *buffer);

const char *efectoTexto(unsigned char efecto);

void limpiarBufferEntrada(void);

#endif // MANEJOCADENAS_H_INCLUDED
