#ifndef JUGAR_H_INCLUDED
#define JUGAR_H_INCLUDED

#include "globales.h"
#include "json.h"
#include "api.h"
#include "mString.h"
#include "manejoArchivos.h"
#include "manejoCadenas.h"
#include "mano.h"
#include "menu.h"
#include "graficos.h"
#include <unistd.h>

#define FALLO_JUGAR -55

#define FALLO_JSON -666

#define CANTIDAD_PUNTOS_GANADORES 12

void armarJsonPost(tJson *jsonPrincipal, tJson *jsonJugador,
                   tConfigAPI *configAPI, const char *nombreJugador,
                   unsigned char cantidadPuntosHumano);
int jugar(const char *nombreJugador, char opcionDificultad,
          tConfigAPI *configAPI);

void aplicarPuntos(tMano *jugadorActual, tMano *jugadorOponente,
                   tCarta *carta, unsigned char *recibioCartaNegativa,
                   unsigned char quienInicia,
                   const tCarta *ultimaCartaDescarte);
tCarta jugarCartaHumano(tMano *humano, unsigned char *posicionCartaJugada);
tCarta jugarCartaMaquina(tMano *maquina, unsigned char *posicionCartaJugada,
                         char dificultad, short int puntosOponente,
                         unsigned char recibioCartaNegativa);

#endif // JUGAR_H_INCLUDED
