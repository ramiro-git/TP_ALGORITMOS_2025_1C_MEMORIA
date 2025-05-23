#include <stdio.h>
#include <stdlib.h>
#include "dos.h"
#define DELAY_STANDARD 50
#define DEFINIR_CARTA(carta) \
    ((carta) == MAS_UNO ? mas_uno : \
    (carta) == MAS_DOS ? mas_dos : \
    (carta) == MENOS_UNO ? menos_uno : \
    (carta) == MENOS_DOS ? menos_dos : \
    (carta) == REPETIR_TURNO ? repetir : \
    (carta) == ESPEJO ? espejo : reverso) \

int main(int argc, char *argv[])
{
    /// DECLARACIONES
    // SDL
    char done = 0;
    SDL_Event evento;
    SDL_Surface *icon;
    SDL_Window* ventana;
    SDL_Renderer* renderer;
    TTF_Font* fuente;
    SDL_Texture *fondo,
                *mas_uno,
                *mas_dos,
                *menos_uno,
                *menos_dos,
                *espejo,
                *repetir,
                *reverso,
                *maso_lleno,
                *nula,
                *aux,
                *pantalla_espera;

    /// SDL - Inicializaciones
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_Log("No se pudo inicializar SDL_image: %s", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    if(TTF_Init() == -1)
    {
        SDL_Log("No se puedo inicializar SDL Fonts: %s", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    fuente = TTF_OpenFont("./fonts/font.ttf", 35);

    ventana = SDL_CreateWindow(
                  "DOS!",
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED,
                  WIDTH, HEIGHT,
                  SDL_WINDOW_SHOWN
              );

    if (!ventana)
    {
        SDL_Log("No se pudo crear la ventana: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("No se pudo crear el renderer: %s", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    // Cargar y establecer ícono
    icon = SDL_LoadBMP("icono.bmp");
    if (!icon)
    {
        printf("Error cargando icono: %s\n", SDL_GetError());
    }
    else
    {
        SDL_SetWindowIcon(ventana, icon);
        SDL_FreeSurface(icon);
    }

    // Cargar fondo
    fondo = IMG_LoadTexture(renderer, "./texturas/fondo.png");
    if (!fondo)
    {
        SDL_Log("No se pudo cargar la textura del fondo: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    //Texturas de las cartas
    if (!(mas_uno = IMG_LoadTexture(renderer, "./texturas/mas_uno.png")))
    {
        SDL_Log("No se pudo cargar la textura de +1: %s", SDL_GetError());
        SDL_DestroyTexture(fondo);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(mas_dos = IMG_LoadTexture(renderer, "./texturas/mas_dos.png")))
    {
        SDL_Log("No se pudo cargar la textura de +2: %s", SDL_GetError());
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(menos_uno = IMG_LoadTexture(renderer, "./texturas/menos_uno.png")))
    {
        SDL_Log("No se pudo cargar la textura de -1: %s", SDL_GetError());
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(menos_dos = IMG_LoadTexture(renderer, "./texturas/menos_dos.png")))
    {
        SDL_Log("No se pudo cargar la textura de -2: %s", SDL_GetError());
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(espejo = IMG_LoadTexture(renderer, "./texturas/espejo.png")))
    {
        SDL_Log("No se pudo cargar la textura de espejo: %s", SDL_GetError());
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(repetir = IMG_LoadTexture(renderer, "./texturas/repetir.png")))
    {
        SDL_Log("No se pudo cargar la textura de repetir: %s", SDL_GetError());
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(reverso = IMG_LoadTexture(renderer, "./texturas/reverso.png")))
    {
        SDL_Log("No se pudo cargar la textura de repetir: %s", SDL_GetError());
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyTexture(repetir);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(maso_lleno = IMG_LoadTexture(renderer, "./texturas/maso_lleno.png")))
    {
        SDL_Log("No se pudo cargar la textura de repetir: %s", SDL_GetError());
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(nula = IMG_LoadTexture(renderer, "./texturas/null.png")))
    {
        SDL_Log("No se pudo cargar la textura de repetir: %s", SDL_GetError());
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    if (!(pantalla_espera = IMG_LoadTexture(renderer, "./texturas/espera.png")))
    {
        SDL_Log("No se pudo cargar la textura de repetir: %s", SDL_GetError());
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
        SDL_DestroyTexture(nula);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    //PANTALLA DE CARGA
    SDL_RenderCopy(renderer, pantalla_espera, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2500);

    //JUEGO
    while(!done)
    {
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
            {
                done = 1;
            }
        }

        //
        SDL_RenderClear(renderer);  // Primero limpiar pantalla
        SDL_RenderCopy(renderer, fondo, NULL, NULL);  // Luego dibuja fondo

        ///Actualizar tablero
        //MANOS JUGADORES
        for(int i = 0; i < (MAX_CARTAS_EN_MANO * 2); i++)
        {
            dibujarCarta(renderer, DEFINIR_CARTA(i), i); //Manda a dibujar
        }

        //MASO
        aux = maso_lleno;
        dibujarMazo(renderer,aux);


        //DESCARTE
        aux = nula;
        dibujarDescarte(renderer,aux);

        // Jugador
        dibujarDatosJugadores(0,"Maquina",9,renderer,fuente);
        dibujarDatosJugadores(1,"Jugador",11,renderer,fuente);

        ///RENDERIZADO
        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY_STANDARD); //Delay hasta el proximo frame
    }


    /// Limpieza
    //Cartas
    SDL_DestroyTexture(repetir);
    SDL_DestroyTexture(espejo);
    SDL_DestroyTexture(menos_dos);
    SDL_DestroyTexture(menos_uno);
    SDL_DestroyTexture(mas_dos);
    SDL_DestroyTexture(mas_uno);
    SDL_DestroyTexture(reverso);
    SDL_DestroyTexture(nula);
    SDL_DestroyTexture(pantalla_espera);

    //Fondo
    SDL_DestroyTexture(fondo);

    //Cosas de SDL
    TTF_CloseFont(fuente);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
