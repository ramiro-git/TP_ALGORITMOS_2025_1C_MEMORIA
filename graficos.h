#ifndef DOCE_H_INCLUDED
#define DOCE_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdlib.h>
#include <stdio.h>

// CONFIGURACION DEL JUEGO
#define WIDTH 1280
#define HEIGHT 720

#define MAX_NOMBRE 31
#define DELAY_STANDARD 1000

#define MARGIN_BORDE 10
#define MARGIN_CARTAS 70
#define ALTO_CARTA 186
#define ANCHO_CARTA 124

// PROTOTIPOS TABLERO
void dibujarMazo(SDL_Renderer *renderer, SDL_Texture *textura);
void dibujarDescarte(SDL_Renderer *renderer, SDL_Texture *textura);
void dibujarCarta(SDL_Renderer *renderer, SDL_Texture *textura, char pos);
void dibujarDatosJugadores(int jugador, const char *nombre, int cantidadPuntos,
                           SDL_Renderer *renderer, TTF_Font *font);
void dibujarTexto(SDL_Renderer *renderer, TTF_Font *font, const char *texto,
                  int x, int y, SDL_Color color);

#endif // DOCE_H_INCLUDED
