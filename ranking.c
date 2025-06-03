#include "ranking.h"

int compararCantidadPartidasGanadas(const void *a, const void *b)
{
    return ((tRankingJugador *)b)->cantidadPartidasGanadas -
           ((tRankingJugador *)a)->cantidadPartidasGanadas;
}

void mostrarRankingJugador(const void *a, FILE *salida)
{
    escribirSalida(stdout, "%s, %d\n", ((tRankingJugador *)a)->nombreJugador,
                   ((tRankingJugador *)a)->cantidadPartidasGanadas);
}

int parsearArrayJugadores(tJson *json, tLista *lista)
{
    char *cursor, clave[MAX_LONGITUD_CADENA];
    tRankingJugador auxJugador;

    if (!json || !json->cadena)
        return FALSO;

    if (esArrayVacio(json))
        return ARRAY_VACIO;

    cursor = json->cadena;

    SALTAR_ESPACIOS(&cursor);

    if (*cursor != '[')
        return FALSO;

    cursor++;

    SALTAR_ESPACIOS(&cursor);

    while (*cursor && *cursor != ']')
    {
        if (*cursor != '{')
        {
            fprintf(stderr, "Error: se esperaba un objeto JSON.\n");

            return FALSO;
        }

        cursor++;

        SALTAR_ESPACIOS(&cursor);

        while (*cursor && *cursor != '}')
        {
            if (!parsearCadena(&cursor, clave))
            {
                fprintf(stderr, "Error al leer clave.\n");

                return FALSO;
            }

            SALTAR_ESPACIOS(&cursor);

            if (*cursor != ':')
            {
                fprintf(stderr, "Falta ':' después de la clave.\n");

                return FALSO;
            }

            cursor++;

            SALTAR_ESPACIOS(&cursor);

            if (!mStrcmp(clave, "nombreJugador"))
            {
                if (!parsearCadena(&cursor, auxJugador.nombreJugador))
                {
                    fprintf(stderr, "Error al parsear nombreJugador.\n");

                    return FALSO;
                }
            }
            else if (!mStrcmp(clave, "cantidadPartidasGanadas"))
            {
                if (!parsearNumero(&cursor,
                                   &(auxJugador.cantidadPartidasGanadas)))
                {
                    fprintf(stderr,
                            "Error al parsear cantidadPartidasGanadas.\n");

                    return FALSO;
                }
            }
            else
                parsearValor(&cursor);

            SALTAR_ESPACIOS(&cursor);

            if (*cursor == ',')
            {
                cursor++;

                SALTAR_ESPACIOS(&cursor);
            }
        }

        if (*cursor != '}')
        {
            fprintf(stderr, "Falta '}' al cerrar objeto.\n");

            return FALSO;
        }

        cursor++;

        if (ponerEnOrden(lista, &auxJugador, sizeof(tRankingJugador),
                         compararCantidadPartidasGanadas, NULL, 1) != VERDADERO)
        {
            fprintf(stderr, "Error al insertar jugador en la lista.\n");

            return FALSO;
        }

        SALTAR_ESPACIOS(&cursor);

        if (*cursor == ',')
        {
            cursor++;

            SALTAR_ESPACIOS(&cursor);
        }
        else if (*cursor != ']')
        {
            fprintf(stderr, "Se esperaba ',' o ']'.\n");

            return FALSO;
        }
    }

    if (*cursor != ']')
    {
        fprintf(stderr, "Falta ']' al final del array.\n");

        return FALSO;
    }

    return VERDADERO;
}
