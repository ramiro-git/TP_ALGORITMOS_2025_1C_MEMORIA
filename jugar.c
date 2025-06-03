#include "jugar.h"

#define DEFINIR_TEXTURA(carta)                                                                                                              \
    ((carta.efecto == EFECTO_NORMAL && carta.puntos == 1) ? mas_uno : (carta.efecto == EFECTO_NORMAL && carta.puntos == 2)      ? mas_dos   \
                                                                  : (carta.efecto == EFECTO_SACAR_PUNTOS && carta.puntos == -1) ? menos_uno \
                                                                  : (carta.efecto == EFECTO_SACAR_PUNTOS && carta.puntos == -2) ? menos_dos \
                                                                  : (carta.efecto == EFECTO_REPETIR)                            ? repetir   \
                                                                  : (carta.efecto == EFECTO_ESPEJO)                             ? espejo    \
                                                                                                                                : reverso)

int jugar(const char *nombreJugador, char opcionDificultad,
          tConfigAPI *configAPI)
{
    unsigned char i, done, quienInicia, posicionCartaJugada,
        recibioCartaNegativa;
    char *nombreArchivoInforme;
    unsigned short int turno, resApi;
    SDL_Surface *icon;
    SDL_Window *ventana;
    SDL_Renderer *renderer;
    TTF_Font *fuente;
    SDL_Texture *fondo, *mas_uno, *mas_dos, *menos_uno, *menos_dos, *espejo,
        *repetir, *reverso, *maso_lleno, *nula, *pantalla_espera;
    tPila mazo, descarte;
    tCarta cartaJugada, cartaRobada, auxCarta, ultimaCartaDescarte;
    tMano humano, maquina, *jugando, *oponente;
    tJson *jsonPrincipal, *jsonJugador;
    FILE *archivoInforme;

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

    if (TTF_Init() == -1)
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
        SDL_WINDOW_SHOWN);

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

    icon = SDL_LoadBMP("./icono.bmp");

    if (!icon)
        printf("Error cargando icono: %s\n", SDL_GetError());
    else
    {
        SDL_SetWindowIcon(ventana, icon);

        SDL_FreeSurface(icon);
    }

    fondo = IMG_LoadTexture(renderer, "./texturas/fondo.png");

    if (!fondo)
    {
        SDL_Log("No se pudo cargar la textura del fondo: %s", SDL_GetError());

        SDL_DestroyRenderer(renderer);

        SDL_DestroyWindow(ventana);

        SDL_Quit();

        return 1;
    }

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
        SDL_Log("No se pudo cargar la textura de reverso: %s", SDL_GetError());

        SDL_DestroyTexture(repetir);
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

    if (!(maso_lleno = IMG_LoadTexture(renderer, "./texturas/maso_lleno.png")))
    {
        SDL_Log("No se pudo cargar la textura de maso: %s", SDL_GetError());

        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
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

    if (!(nula = IMG_LoadTexture(renderer, "./texturas/null.png")))
    {
        SDL_Log("No se pudo cargar la textura nula: %s", SDL_GetError());

        SDL_DestroyTexture(maso_lleno);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
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

    if (!(pantalla_espera = IMG_LoadTexture(renderer, "./texturas/espera.png")))
    {
        SDL_Log("No se pudo cargar la textura de espera: %s", SDL_GetError());

        SDL_DestroyTexture(nula);
        SDL_DestroyTexture(maso_lleno);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
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

    nombreArchivoInforme = generarNombreArchivo();
    archivoInforme = fopen(nombreArchivoInforme, CONSTANTE_ESCRITURA);

    if (!archivoInforme)
    {
        SDL_DestroyTexture(nula);
        SDL_DestroyTexture(maso_lleno);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);

        SDL_DestroyRenderer(renderer);

        SDL_DestroyWindow(ventana);

        SDL_Quit();

        return FALLO_ESCRITURA;
    }

    crearPila(&mazo);
    crearPila(&descarte);

    jsonPrincipal = crearJson();

    if (!jsonPrincipal)
    {
        fclose(archivoInforme);

        vaciarPila(&mazo);
        vaciarPila(&descarte);

        SDL_DestroyTexture(nula);
        SDL_DestroyTexture(maso_lleno);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);

        SDL_DestroyRenderer(renderer);

        SDL_DestroyWindow(ventana);

        SDL_Quit();

        fprintf(stderr, "Error, no se pudo crear el JSON\n");

        return FALLO_JSON;
    }

    jsonJugador = crearJson();

    if (!jsonJugador)
    {
        fclose(archivoInforme);

        vaciarPila(&mazo);
        vaciarPila(&descarte);

        destruirJson(jsonPrincipal);

        SDL_DestroyTexture(nula);
        SDL_DestroyTexture(maso_lleno);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);

        SDL_DestroyRenderer(renderer);

        SDL_DestroyWindow(ventana);

        SDL_Quit();

        fprintf(stderr, "Error, no se pudo crear el JSON\n");

        return FALLO_JSON;
    }

    srand((unsigned)time(NULL));

    /// Crea el mazo y se mezcla
    if (crearMazoYMezclar(&mazo) == MAZO_LLENO)
    {
        fclose(archivoInforme);

        vaciarPila(&mazo);
        vaciarPila(&descarte);

        destruirJson(jsonPrincipal);
        destruirJson(jsonJugador);

        SDL_DestroyTexture(nula);
        SDL_DestroyTexture(maso_lleno);
        SDL_DestroyTexture(reverso);
        SDL_DestroyTexture(repetir);
        SDL_DestroyTexture(espejo);
        SDL_DestroyTexture(menos_dos);
        SDL_DestroyTexture(menos_uno);
        SDL_DestroyTexture(mas_dos);
        SDL_DestroyTexture(mas_uno);
        SDL_DestroyTexture(fondo);

        SDL_DestroyRenderer(renderer);

        SDL_DestroyWindow(ventana);

        SDL_Quit();

        fprintf(stderr, "Error al inicializar la partida\n");

        return FALLO_JUGAR;
    }

    inicializarJson(jsonPrincipal, NULL);
    inicializarJson(jsonJugador, NULL);

    inicializarMano(&humano, FALSO);
    inicializarMano(&maquina, FALSO);

    /// Se reparte 3 cartas a cada uno
    repartirCartas(&mazo, &humano);
    repartirCartas(&mazo, &maquina);

    /// Se inicia a alguno de los dos de forma aleatoria
    quienInicia = rand() % 2;

    recibioCartaNegativa = 0;
    turno = 0;
    done = 0;

    fprintf(stdout, "Quien inicia: %s\n", quienInicia == FALSO ? "Humano" : "Maquina");

    SDL_RenderCopy(renderer, pantalla_espera, NULL, NULL);
    SDL_RenderPresent(renderer);

    while (humano.cantidadPuntos < CANTIDAD_PUNTOS_GANADORES &&
           maquina.cantidadPuntos < CANTIDAD_PUNTOS_GANADORES && !done)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fondo, NULL, NULL);

        for (i = 0; i < maquina.cantidadCartas; i++)
            dibujarCarta(renderer, DEFINIR_TEXTURA(maquina.cartas[i]), i);

        for (i = 0; i < humano.cantidadCartas; i++)
            dibujarCarta(renderer, DEFINIR_TEXTURA(humano.cartas[i]), i + 3);

        dibujarMazo(renderer, pilaVacia(&mazo) ? nula : maso_lleno);

        if (pilaVacia(&descarte))
            dibujarDescarte(renderer, nula);
        else
        {
            verTope(&descarte, &auxCarta, sizeof(tCarta));

            dibujarDescarte(renderer, DEFINIR_TEXTURA(auxCarta));
        }

        // Mostrar puntos reales de cada jugador
        dibujarDatosJugadores(0, "Maquina", maquina.cantidadPuntos, renderer,
                              fuente);
        dibujarDatosJugadores(1, nombreJugador, humano.cantidadPuntos, renderer,
                              fuente);

        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY_STANDARD); // Espera entre turnos

        /// JUEGO
        fprintf(stdout, "\n\nPuntos humano: %d\n", humano.cantidadPuntos);
        fprintf(stdout, "Puntos maquina: %d\n", maquina.cantidadPuntos);

        jugando = (quienInicia == FALSO) ? &humano : &maquina;
        oponente = (quienInicia == FALSO) ? &maquina : &humano;

        /// Se juega una carta
        if (quienInicia == FALSO)
            cartaJugada = jugarCartaHumano(jugando, &posicionCartaJugada);
        else
            cartaJugada = jugarCartaMaquina(jugando, &posicionCartaJugada,
                                            opcionDificultad,
                                            oponente->cantidadPuntos,
                                            recibioCartaNegativa);

        escribirSalida(archivoInforme, "%s|%d|%hd\n", (quienInicia == FALSO) ? "Humano" : "Maquina", cartaJugada.efecto,
                       cartaJugada.puntos);

        fprintf(stdout, "Carta jugada: %hd puntos, efecto %s\n", cartaJugada.puntos,
               efectoTexto(cartaJugada.efecto));

        if (verTope(&descarte, &ultimaCartaDescarte, sizeof(tCarta)) != EXITO_PILA_VISTA_TOPE)
            fprintf(stderr, "Descarte vacio\n");

        aplicarPuntos(jugando, oponente, &cartaJugada, &recibioCartaNegativa,
                      quienInicia, !turno ? NULL : &ultimaCartaDescarte);

        if (apilar(&descarte, &cartaJugada, sizeof(tCarta)) != EXITO_PILA_APILADA)
            fprintf(stderr, "Error - Mazo de descarte lleno\n");

        eliminarCartaPorPosicion(jugando, posicionCartaJugada);

        if (pilaVacia(&mazo) && !recargarMazoDesdeDescarte(&mazo, &descarte))
            fprintf(stderr, "No quedan cartas para recargar el mazo\n");

        if (!pilaVacia(&mazo))
        {
            verTope(&mazo, &cartaRobada, sizeof(tCarta));

            fprintf(stdout, "Robando: %hd puntos, efecto %s\n",
                    cartaRobada.puntos, efectoTexto(cartaRobada.efecto));

            if (desapilar(&mazo, &jugando->cartas[jugando->cantidadCartas],
                          sizeof(tCarta)) == EXITO_PILA_DESAPILADA)
                jugando->cantidadCartas++;
            else
                fprintf(stderr, "Error - No se pudo robar carta\n");
        }

        if (quienInicia != FALSO)
            putchar('\n');

        if (cartaJugada.efecto != EFECTO_REPETIR)
            quienInicia = !quienInicia;

        turno++;
    }

    humano.cantidadPuntos >= CANTIDAD_PUNTOS_GANADORES
        ? fprintf(stdout, "\nFelicitaciones, ganaste\n")
        : fprintf(stdout, "\nPerdiste\n");

    sleep(TIEMPO_ESPERA);

    escribirSalida(archivoInforme, "%d|%d|%s\n", humano.cantidadPuntos,
                   maquina.cantidadPuntos, humano.cantidadPuntos >= CANTIDAD_PUNTOS_GANADORES ? "Humano" : "Maquina");

    vaciarPila(&mazo);
    vaciarPila(&descarte);

    fclose(archivoInforme);

    armarJsonPost(jsonPrincipal, jsonJugador, configAPI, nombreJugador,
                  humano.cantidadPuntos);

    cerrarJson(jsonJugador);

    objetoAJson(jsonPrincipal, "jugador", jsonJugador);

    cerrarJson(jsonPrincipal);

    if ((resApi = (llamarAPI(configAPI, "POST", jsonPrincipal))) != VERDADERO)
        fprintf(stderr, "Fallo en la API. Codigo de error %d\n", resApi);

    destruirJson(jsonPrincipal);
    destruirJson(jsonJugador);

    /// LIMPIEZA SDL
    // Texturas de cartas
    SDL_DestroyTexture(repetir);
    SDL_DestroyTexture(espejo);
    SDL_DestroyTexture(menos_dos);
    SDL_DestroyTexture(menos_uno);
    SDL_DestroyTexture(mas_dos);
    SDL_DestroyTexture(mas_uno);
    SDL_DestroyTexture(reverso);
    SDL_DestroyTexture(nula);
    SDL_DestroyTexture(maso_lleno);
    SDL_DestroyTexture(pantalla_espera);

    // Fondo
    SDL_DestroyTexture(fondo);

    // Limpieza SDL
    TTF_CloseFont(fuente);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    IMG_Quit();
    SDL_Quit();

    limpiarBufferEntrada();

    return VERDADERO;
}

void aplicarPuntos(tMano *jugadorActual, tMano *jugadorOponente,
                   tCarta *carta, unsigned char *recibioCartaNegativa,
                   unsigned char quienInicia, const tCarta *ultimaCartaDescarte)
{
    if (carta->puntos < 0)
    {
        if (jugadorOponente->cantidadPuntos + carta->puntos < 0)
            jugadorOponente->cantidadPuntos = 0;
        else
            jugadorOponente->cantidadPuntos += carta->puntos;

        if (!quienInicia)
            *recibioCartaNegativa = 1;
    }
    else if (carta->efecto == EFECTO_ESPEJO && ultimaCartaDescarte &&
             ultimaCartaDescarte->puntos < 0)
    {
        jugadorActual->cantidadPuntos -= ultimaCartaDescarte->puntos;

        if (jugadorOponente->cantidadPuntos + ultimaCartaDescarte->puntos < 0)
            jugadorOponente->cantidadPuntos = 0;
        else
            jugadorOponente->cantidadPuntos += ultimaCartaDescarte->puntos;
    }
    else
    {
        if (!quienInicia)
            *recibioCartaNegativa = 0;

        jugadorActual->cantidadPuntos += carta->puntos;
    }
}

tCarta jugarCartaHumano(tMano *humano, unsigned char *posicionCartaJugada)
{
    unsigned i, indice = 0;

    // Muestra mano del jugador
    printf("Tu mano:\n\n");
    for (i = 0; i < humano->cantidadCartas; i++)
        fprintf(stdout, " [%u] %hd puntos, efecto %s\n", i, humano->cartas[i].puntos,
               efectoTexto(humano->cartas[i].efecto));

    // Pide la posicion
    do
    {
        printf("\nIndice: ");
        if (scanf("%u", &indice) != 1)
        {
            limpiarBufferEntrada();
            indice = humano->cantidadCartas;
        }
    } while (indice >= humano->cantidadCartas);

    *posicionCartaJugada = (unsigned char)indice;

    return humano->cartas[indice];
}

tCarta jugarCartaMaquina(tMano *maquina, unsigned char *posicionCartaJugada,
                         char dificultad, short int puntosOponente,
                         unsigned char recibioCartaNegativa)
{
    unsigned char cartasBuenas = 0, mejorCartaEncontrada = 0;
    unsigned i, cartaSeleccionada = 0;

    for (i = 0; i < maquina->cantidadCartas; i++)
        fprintf(stdout, " [Maquina %u] %hd puntos, efecto %s\n", i,
               maquina->cartas[i].puntos,
               efectoTexto(maquina->cartas[i].efecto));

    switch (dificultad)
    {
    /// Facil
    case 'a':
        cartaSeleccionada = rand() % maquina->cantidadCartas;
        break;
    /// Media
    case 'b':
        // Si la maquina esta por ganar, se prioriza meter puntos
        if (maquina->cantidadPuntos >= (rand() % 2 + 8))
        {
            for (i = 0; i < maquina->cantidadCartas && !mejorCartaEncontrada;
                 i++)
            {
                // Si encuentro una, la juego y salgo
                if (maquina->cartas[i].efecto == EFECTO_NORMAL)
                {
                    if (maquina->cartas[i].puntos == 2)
                    {
                        cartaSeleccionada = i;

                        mejorCartaEncontrada = 1;
                    }
                    else
                        cartaSeleccionada = i;
                }
            }
        }
        else if (!puntosOponente) // Si el jugador no tiene puntos, priorizo cualquier otra carta
        {
            for (i = 0; i < maquina->cantidadCartas && !mejorCartaEncontrada;
                 i++)
            {
                if (maquina->cartas[i].puntos >= 0)
                {
                    cartaSeleccionada = i;

                    mejorCartaEncontrada = 1;
                }
            }
        }
        else
            // Si no se cumplio ninguna de las condiciones de arriba
            // La maquina es libre de usar cualquier carta
            cartaSeleccionada = rand() % maquina->cantidadCartas;
        break;
    /// Dificil
    case 'c':
        // Si se recibio carta negativa, se prioriza espejo
        // Nota:
        // Esto es compatible con priorizar sacarle puntos
        // Si esta cerca de ganar
        if (recibioCartaNegativa)
        {
            for (i = 0; i < maquina->cantidadCartas && !mejorCartaEncontrada;
                 i++)
            {
                if (maquina->cartas[i].efecto == EFECTO_ESPEJO)
                {
                    cartaSeleccionada = i;

                    mejorCartaEncontrada = 1;
                }
            }
        }

        if (!mejorCartaEncontrada)
        {
            for (i = 0; i < maquina->cantidadCartas; i++)
                if (maquina->cartas[i].puntos == 2 ||
                    maquina->cartas[i].puntos == -2)
                    cartasBuenas++;

            if (cartasBuenas > 1)
            {
                for (i = 0; i < maquina->cantidadCartas &&
                            !mejorCartaEncontrada;
                     i++)
                {
                    if (maquina->cartas[i].efecto == EFECTO_REPETIR)
                    {
                        cartaSeleccionada = i;

                        mejorCartaEncontrada = 1;
                    }
                }
            }
        }

        if (!mejorCartaEncontrada &&
            maquina->cantidadPuntos >= (rand() % 2 + 8))
        {
            for (i = 0; i < maquina->cantidadCartas && !mejorCartaEncontrada;
                 i++)
            {
                if (maquina->cartas[i].efecto == EFECTO_NORMAL)
                {
                    if (maquina->cartas[i].puntos == 2)
                    {
                        cartaSeleccionada = i;

                        mejorCartaEncontrada = 1;
                    }
                    else
                        cartaSeleccionada = i;
                }
            }
        }
        else if (!mejorCartaEncontrada && puntosOponente >= (rand() % 2 + 8))
        {
            for (i = 0; i < maquina->cantidadCartas && !mejorCartaEncontrada;
                 i++)
            {
                if (maquina->cartas[i].efecto == EFECTO_SACAR_PUNTOS)
                {
                    if (maquina->cartas[i].puntos == -2)
                    {
                        cartaSeleccionada = i;

                        mejorCartaEncontrada = 1;
                    }
                    else
                        cartaSeleccionada = i;
                }
            }
        }
        else if (!mejorCartaEncontrada && !puntosOponente)
        {
            for (i = 0; i < maquina->cantidadCartas && !mejorCartaEncontrada;
                 i++)
            {
                if (maquina->cartas[i].puntos >= 0)
                {
                    cartaSeleccionada = i;

                    mejorCartaEncontrada = 1;
                }
            }
        }
        else if (!mejorCartaEncontrada)
            cartaSeleccionada = rand() % maquina->cantidadCartas;
        break;
    }

    *posicionCartaJugada = (unsigned char)cartaSeleccionada;

    return maquina->cartas[cartaSeleccionada];
}

void armarJsonPost(tJson *jsonPrincipal, tJson *jsonJugador,
                   tConfigAPI *configAPI, const char *nombreJugador,
                   unsigned char cantidadPuntosHumano)
{
    unsigned char quienGano = cantidadPuntosHumano >=
                                      CANTIDAD_PUNTOS_GANADORES
                                  ? 1
                                  : 0;

    cadenaAJson(jsonPrincipal, "codigoGrupo", configAPI->codigoGrupo);

    cadenaAJson(jsonJugador, "nombre", nombreJugador);

    numeroAJson(jsonJugador, "vencedor",
                &quienGano,
                convertirUnsignedCharACadena);
}
