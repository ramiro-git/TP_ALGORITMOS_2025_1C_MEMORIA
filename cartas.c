#include "cartas.h"

// Mezcla cartas usando algoritmo Fisher-Yates
void mezclar(tCarta *cartas, unsigned cantidadCartas)
{
    unsigned i, j;
    tCarta temporal;

    for (i = cantidadCartas - 1; i > 0; i--)
    {
        j = (unsigned)(rand() % (i + 1));

        temporal = cartas[i];

        cartas[i] = cartas[j];
        cartas[j] = temporal;
    }
}
