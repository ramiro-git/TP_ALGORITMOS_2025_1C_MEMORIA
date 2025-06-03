#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include "globales.h"
#include "lista.h"
#include "manejoArchivos.h"
#include "json.h"

typedef struct
{
    char nombreJugador[TAM_NOMBRE_JUGADOR];
    unsigned cantidadPartidasGanadas;
} tRankingJugador;

int compararCantidadPartidasGanadas(const void *a, const void *b);

void mostrarRankingJugador(const void *a, FILE *salida);

int parsearArrayJugadores(tJson *json, tLista *lista);

#endif // RANKING_H_INCLUDED
