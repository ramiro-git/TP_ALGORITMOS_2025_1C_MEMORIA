#include "mano.h"

int crearMazoYMezclar(tPila *mazo)
{
    unsigned i;
    const unsigned char limiteDosPuntos = CANTIDAD_CARTAS_2_PUNTOS;
    const unsigned char limiteUnPuntos = limiteDosPuntos +
                                         CANTIDAD_CARTAS_1_PUNTOS;
    const unsigned char limiteMenosUnPuntos = limiteUnPuntos +
                                              CANTIDAD_CARTAS_MENOS_1_PUNTOS;
    const unsigned char limiteMenosDos = limiteMenosUnPuntos +
                                         CANTIDAD_CARTAS_MENOS_2_PUNTOS;
    const unsigned char limiteRepetir = limiteMenosDos +
                                        CANTIDAD_CARTAS_REPETIR_TURNO;
    tCarta cartas[CANTIDAD_CARTAS];

    for (i = 0; i < CANTIDAD_CARTAS; i++)
    {
        if (i < limiteDosPuntos)
        {
            cartas[i].puntos = 2;
            cartas[i].efecto = EFECTO_NORMAL;
        }
        else if (i < limiteUnPuntos)
        {
            cartas[i].puntos = 1;
            cartas[i].efecto = EFECTO_NORMAL;
        }
        else if (i < limiteMenosUnPuntos)
        {
            cartas[i].puntos = -1;
            cartas[i].efecto = EFECTO_SACAR_PUNTOS;
        }
        else if (i < limiteMenosDos)
        {
            cartas[i].puntos = -2;
            cartas[i].efecto = EFECTO_SACAR_PUNTOS;
        }
        else if (i < limiteRepetir)
        {
            cartas[i].puntos = 0;
            cartas[i].efecto = EFECTO_REPETIR;
        }
        else
        {
            cartas[i].puntos = 0;
            cartas[i].efecto = EFECTO_ESPEJO;
        }
    }

    mezclar(cartas, CANTIDAD_CARTAS);

    return cargarMazoEnPila(mazo, cartas);
}

int cargarMazoEnPila(tPila *mazo, tCarta *cartas)
{
    unsigned i;

    for (i = 0; i < CANTIDAD_CARTAS; i++)
    {
        if (apilar(mazo, &cartas[i], sizeof(tCarta)) != EXITO_PILA_APILADA)
        {
            fprintf(stderr, "Error - Mazo lleno\n");

            return MAZO_LLENO;
        }
    }

    return VERDADERO;
}

void inicializarMano(tMano *entidad, int valor)
{
    mMemset(entidad->cartas, valor, CANTIDAD_CARTAS_MANO * sizeof(tCarta));
    entidad->cantidadPuntos = 0;
    entidad->cantidadCartas = CANTIDAD_CARTAS_MANO;
}

void repartirCartas(tPila *mazo, tMano *entidad)
{
    unsigned i;

    for (i = 0; i < CANTIDAD_CARTAS_MANO; i++)
        if (desapilar(mazo, &entidad->cartas[i], sizeof(tCarta)) != EXITO_PILA_DESAPILADA)
            fprintf(stderr, "Error - Mazo vacio\n");
}

void eliminarCartaPorPosicion(tMano *entidad,
                              unsigned char posicionCartaJugada)
{
    unsigned i;

    for (i = posicionCartaJugada; i + 1 < entidad->cantidadCartas; i++)
        entidad->cartas[i] = entidad->cartas[i + 1];

    entidad->cantidadCartas--;
}

unsigned char recargarMazoDesdeDescarte(tPila *mazo, tPila *descarte)
{
    unsigned i, cantidad = 0;
    tCarta buffer[CANTIDAD_CARTAS];

    mMemset(buffer, 0, sizeof(buffer));

    while (desapilar(descarte, &buffer[cantidad], sizeof(tCarta)) == EXITO_PILA_DESAPILADA)
        cantidad++;

    if (!cantidad)
        return FALSO;

    /** Se mezcla nuevamente **/
    mezclar(buffer, cantidad);

    /** Volver a cargar en el mazo **/
    for (i = 0; i < cantidad; i++)
        if (apilar(mazo, &buffer[i], sizeof(tCarta)) != EXITO_PILA_APILADA)
            return FALSO;

    return VERDADERO;
}
