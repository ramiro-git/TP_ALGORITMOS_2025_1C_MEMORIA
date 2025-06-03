#ifndef CARTAS_H_INCLUDED
#define CARTAS_H_INCLUDED

#include <stdlib.h>

#define CANTIDAD_CARTAS 40
#define CANTIDAD_CARTAS_MANO 3

#define CANTIDAD_CARTAS_2_PUNTOS 6
#define CANTIDAD_CARTAS_1_PUNTOS 10
#define CANTIDAD_CARTAS_MENOS_1_PUNTOS 8
#define CANTIDAD_CARTAS_MENOS_2_PUNTOS 6
#define CANTIDAD_CARTAS_REPETIR_TURNO 6
#define CANTIDAD_CARTAS_ESPEJO 4

typedef struct
{
    short int puntos;
    unsigned char efecto;
} tCarta;

void mezclar(tCarta *cartas, unsigned cantidadCartas);

#endif // CARTAS_H_INCLUDED
