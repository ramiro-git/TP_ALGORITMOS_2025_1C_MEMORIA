#include "lista.h"

#define MINIMO(X, Y) ((X) <= (Y) ? (X) : (Y))

void crearLista(tLista *lista)
{
    *lista = NULL;
}

int ponerEnOrden(tLista *lista, const void *dato, unsigned tamDato,
                 tComparar comparar, tAcumular acumular,
                 unsigned char duplicados)
{
    tNodo *insertar;

    while (*lista && comparar((*lista)->info, dato) < 0)
        lista = &(*lista)->siguiente;

    if (*lista && !comparar((*lista)->info, dato))
    {
        if (!duplicados)
        {
            if (acumular)
            {
                if (!acumular(&(*lista)->info, &(*lista)->tamInfo, dato,
                              tamDato))
                    return FALLO_MEMORIA;
            }

            return ELEMENTO_DUPLICADO;
        }
    }

    insertar = (tNodo *)malloc(sizeof(tNodo));

    if (!insertar)
        return FALLO_MEMORIA;

    insertar->info = malloc(tamDato);

    if (!insertar->info)
    {
        free(insertar);

        return FALLO_MEMORIA;
    }

    mMemcpy(insertar->info, dato, tamDato);
    insertar->tamInfo = tamDato;
    insertar->siguiente = *lista;

    *lista = insertar;

    return VERDADERO;
}

void vaciarListaYMostrar(tLista *lista, Mostrar mostrar, FILE *archivo)
{
    tNodo *actual;

    while (*lista)
    {
        actual = *lista;

        *lista = actual->siguiente;

        if (mostrar && archivo)
            mostrar(actual->info, archivo);

        free(actual->info);
        free(actual);
    }
}
