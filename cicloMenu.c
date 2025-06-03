#include "cicloMenu.h"

int cicloMenu()
{
    int resMostrarRanking;
    char opcionDecision, opcionDificultad;
    char nombreJugador[TAM_NOMBRE_JUGADOR];
    tConfigAPI configAPI;

    inicializarCargaConfigAPI(&configAPI);

    do
    {
        opcionDecision = pedirOpcion(
            "Selecciona una opcion:\n"
            "[A] Jugar\n"
            "[B] Ver ranking\n"
            "[C] Salir\n\nIngrese opcion: ",
            "ABC");
        switch (opcionDecision)
        {
        case 'a':
            if (!verificarArchivoLeido(&configAPI, ARCHIVO_API,
                                       CONSTANTE_LECTURA))
                return FALLO_LECTURA;

            pedirNombre(nombreJugador, TAM_NOMBRE_JUGADOR);

            opcionDificultad = pedirOpcion(
                "Selecciona la dificultad:\n"
                "[A] Facil\n"
                "[B] Medio\n"
                "[C] Dificil\n\nIngrese opcion: ",
                "ABC");

            jugar(nombreJugador, opcionDificultad, &configAPI);

            break;
        case 'b':
            if (!verificarArchivoLeido(&configAPI, ARCHIVO_API,
                                       CONSTANTE_LECTURA))
                return FALLO_LECTURA;

            if ((resMostrarRanking = mostrarRanking(&configAPI) == ARRAY_VACIO))
                fprintf(stdout, "El array esta vacio\n");
            else if (resMostrarRanking == FALLO_MEMORIA)
                fprintf(stderr, "Fallo al mostrar el ranking\n");

            break;
        case 'c':
            fprintf(stdout, "Hasta luego!\n");

            break;
        }
    } while (opcionDecision != 'c');

    return VERDADERO;
}

int mostrarRanking(tConfigAPI *configAPI)
{
    int resParseo;
    tLista lista;
    tJson *jsonGET = crearJson();

    if (!jsonGET)
        return FALLO_MEMORIA;

    short int resAPI = llamarAPI(configAPI, "GET", jsonGET);

    if (resAPI)
    {
        crearLista(&lista);

        resParseo = parsearArrayJugadores(jsonGET, &lista);

        if (resParseo == ARRAY_VACIO)
        {
            printf("Grupo de Rankings vacio...\n");

            sleep(TIEMPO_ESPERA);

            destruirJson(jsonGET);

            return ARRAY_VACIO;
        }
        else if (resParseo == FALSO)
            fprintf(stderr, "Error al parsear personas.\n");

        vaciarListaYMostrar(&lista, mostrarRankingJugador, stdout);

        puts("Presionar ENTER para regresar...");
        getchar();

        system("cls");
    }
    else if (resAPI == CODIGO_MALA_RESPUESTA)
        fprintf(stderr, "Actualmente no hay informacion en la API de %s\n",
                configAPI->codigoGrupo);
    else
        fprintf(stderr, "Error desconocido\n");

    destruirJson(jsonGET);

    return VERDADERO;
}
