#include "graficos.h"

/// TABLERO
void dibujarMazo(SDL_Renderer *renderer, SDL_Texture *textura)
{
    SDL_Rect dst = {(WIDTH / 2) - (ANCHO_CARTA / 2) + MARGIN_CARTAS,
                    HEIGHT / 2 - (ALTO_CARTA / 2), ANCHO_CARTA, ALTO_CARTA};

    SDL_RenderCopy(renderer, textura, NULL, &dst);
}

void dibujarDescarte(SDL_Renderer *renderer, SDL_Texture *textura)
{
    SDL_Rect dst = {(WIDTH / 2) - 2 * (ANCHO_CARTA) + MARGIN_CARTAS,
                    HEIGHT / 2 - (ALTO_CARTA / 2), ANCHO_CARTA, ALTO_CARTA};

    SDL_RenderCopy(renderer, textura, NULL, &dst);
}

// NOTA: Para poner una carta en el centro, la distancia en X es -mas o menos- en 558.
// Que es = (1280 (ancho de la pantalla) / 2) - (165 (ancho de una carta) / 2)
void dibujarCarta(SDL_Renderer *renderer, SDL_Texture *textura, char pos)
{
    int x; // <<<--- Distancia desde el borde izquierdo
    int y; // <<<---- Distancia desde el borde superior

    // DECIDE DONDE DIBUJAR EN FUNCION DE LA POSICION
    switch (pos)
    {
    // Parte superior - Jugador 1
    case 0:
        x = ((WIDTH / 2) - (ANCHO_CARTA / 2)) - ANCHO_CARTA - MARGIN_CARTAS;
        y = MARGIN_BORDE;

        break;
    case 1:
        x = (WIDTH / 2) - (ANCHO_CARTA / 2);
        y = MARGIN_BORDE;

        break;
    case 2:
        x = ((WIDTH / 2) - (ANCHO_CARTA / 2)) + ANCHO_CARTA + MARGIN_CARTAS;
        y = MARGIN_BORDE;

        break;
    // Parte inferior - Jugador 2
    case 3:
        x = ((WIDTH / 2) - (ANCHO_CARTA / 2)) - ANCHO_CARTA - MARGIN_CARTAS;
        y = HEIGHT - ALTO_CARTA - MARGIN_BORDE;

        break;
    case 4:
        x = (WIDTH / 2) - (ANCHO_CARTA / 2);
        y = HEIGHT - ALTO_CARTA - MARGIN_BORDE;

        break;
    case 5:
        x = ((WIDTH / 2) - (ANCHO_CARTA / 2)) + ANCHO_CARTA + MARGIN_CARTAS;
        y = HEIGHT - ALTO_CARTA - MARGIN_BORDE;

        break;
    default:
        // Posición por defecto en el centro
        x = (WIDTH / 2) - (ANCHO_CARTA / 2);
        y = (HEIGHT / 2) - (ALTO_CARTA / 2);

        break;
    }

    SDL_Rect dst = {x, y, ANCHO_CARTA, ALTO_CARTA};

    SDL_RenderCopy(renderer, textura, NULL, &dst);
}

void dibujarDatosJugadores(int jugador, const char *nombre, int cantidadPuntos,
                           SDL_Renderer *renderer, TTF_Font *font)
{
    int x, y;
    char puntos[7];
    SDL_Color color = {255, 255, 255};

    if (jugador == 0) // Maquina
    {
        x = 200;
        y = 70;
    }
    else if (jugador == 1) // Jugador
    {
        x = 1000;
        y = 600;
    }
    else
        return;

    sprintf(puntos, "%d", cantidadPuntos);

    dibujarTexto(renderer, font, nombre, x, y, color);
    dibujarTexto(renderer, font, puntos, x, y + 50, color);
}

void dibujarTexto(SDL_Renderer *renderer, TTF_Font *font, const char *texto,
                  int x, int y, SDL_Color color)
{
    // Nota: El proceso de dibujado de SDL es el siguiente
    //  Dibuja la font sobre una superficie-> Lo manda a una textura (que es con lo que dibuja SDL)
    //  -> Lo "copia"sobre el renderer.
    SDL_Surface *superficie;
    SDL_Texture *textura;
    SDL_Rect destino;

    // Pase a superficie
    superficie = TTF_RenderText_Blended(font, texto, color);

    // Pase a textura
    textura = SDL_CreateTextureFromSurface(renderer, superficie);

    // Creacion destino
    destino.x = x;
    destino.y = y;
    destino.w = superficie->w;
    destino.h = superficie->h;

    // Copia al renderer
    SDL_RenderCopy(renderer, textura, NULL, &destino);

    // Libera
    SDL_FreeSurface(superficie);
    SDL_DestroyTexture(textura);
}
