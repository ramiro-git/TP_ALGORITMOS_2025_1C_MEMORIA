#ifndef DOS_H_INCLUDED
#define DOS_H_INCLUDED


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

//CONFIGURACION DEL JUEGO
#define WIDTH 1280
#define HEIGHT 720

#define MAX_NOMBRE 31
#define MAX_CARTAS_EN_MANO 3
#define MAX_MASO 40
#define PUNTAJE_GANADOR 12

// CARTAS
#define CANTIDAD_CARTAS 6

#define MAS_UNO 1
#define MAS_DOS 2
#define MENOS_UNO -1
#define MENOS_DOS -2
#define REPETIR_TURNO 20
#define ESPEJO 50

//PROTOTIPOS TABLERO
void dibujarMazo(SDL_Renderer* renderer, SDL_Texture* textura);
void dibujarDescarte(SDL_Renderer* renderer, SDL_Texture* textura);
void dibujarCarta(SDL_Renderer* renderer, SDL_Texture* textura, char pos);
void dibujarDatosJugadores(int jugador, char* nombre, int cantidadPuntos, SDL_Renderer* renderer, TTF_Font* font);
void dibujarTexto(SDL_Renderer* renderer, TTF_Font* font, const char* texto, int x, int y, SDL_Color color);

#endif // DOS_H_INCLUDED
