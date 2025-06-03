#ifndef MANO_H_INCLUDED
#define MANO_H_INCLUDED

#include "cartas.h"
#include "pila.h"

#define VERDADERO 1
#define FALSO 0

#define MAZO_LLENO -5

#define EFECTO_NORMAL 0
#define EFECTO_REPETIR 1
#define EFECTO_ESPEJO 2
#define EFECTO_SACAR_PUNTOS 3

typedef struct
{
    tCarta cartas[CANTIDAD_CARTAS_MANO];
    unsigned char cantidadCartas; /// Para saber cuántas tiene
    unsigned char cantidadPuntos;
} tMano;

int crearMazoYMezclar(tPila *mazo);
int cargarMazoEnPila(tPila *mazo, tCarta *cartas);

void inicializarMano(tMano *entidad, int valor);
void repartirCartas(tPila *mazo, tMano *entidad);

void eliminarCartaPorPosicion(tMano *entidad,
                              unsigned char posicionCartaJugada);

unsigned char recargarMazoDesdeDescarte(tPila *mazo, tPila *descarte);

#endif // MANO_H_INCLUDED
