#include "pila.h"

#define MINIMO(A, B) ((A) <= (B) ? (A) : (B))

void crearPila(tPila *pila)
{
    pila->tope = TAM_PILA;
}

int apilar(tPila *pila, const void *dato, unsigned tamDato)
{
    if (pila->tope < tamDato + sizeof(unsigned))
        return FALLO_PILA_LLENA;

    pila->tope -= tamDato;

    mMemcpy(pila->pila + pila->tope, dato, tamDato);

    pila->tope -= sizeof(unsigned);

    mMemcpy(pila->pila + pila->tope, &tamDato, sizeof(unsigned));

    return EXITO_PILA_APILADA;
}

unsigned char pilaVacia(const tPila *pila)
{
    return pila->tope == TAM_PILA;
}

int verTope(const tPila *pila, void *dato, unsigned tamDato)
{
    unsigned auxTamPila;

    if (pila->tope == TAM_PILA)
        return FALLO_PILA_VACIA;

    mMemcpy(&auxTamPila, pila->pila + pila->tope, sizeof(unsigned));

    mMemcpy(dato, pila->pila + pila->tope + sizeof(unsigned), MINIMO(auxTamPila, tamDato));

    return EXITO_PILA_VISTA_TOPE;
}

int desapilar(tPila *pila, void *dato, unsigned tamDato)
{
    unsigned auxTamPila;

    if (pila->tope == TAM_PILA)
        return FALLO_PILA_VACIA;

    mMemcpy(&auxTamPila, pila->pila + pila->tope, sizeof(unsigned));

    pila->tope += sizeof(unsigned);

    mMemcpy(dato, pila->pila + pila->tope, MINIMO(tamDato, auxTamPila));

    pila->tope += auxTamPila;

    return EXITO_PILA_DESAPILADA;
}

void vaciarPila(tPila *pila)
{
    pila->tope = TAM_PILA;
}
