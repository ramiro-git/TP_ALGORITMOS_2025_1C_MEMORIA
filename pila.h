#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stddef.h>
#include "mString.h"

#define TAM_PILA 1024

#define EXITO_PILA_APILADA 1
#define EXITO_PILA_DESAPILADA 1
#define EXITO_PILA_VISTA_TOPE 1

#define PILA_LLENA 1
#define PILA_NO_LLENA 0

#define FALLO_PILA_LLENA -1
#define FALLO_PILA_VACIA -2

typedef struct
{
    char pila[TAM_PILA];
    unsigned tope;
} tPila;

void crearPila(tPila *pila);
int apilar(tPila *pila, const void *dato, unsigned tamDato);
unsigned char pilaVacia(const tPila *pila);
int verTope(const tPila *pila, void *dato, unsigned tamDato);
int desapilar(tPila *pila, void *dato, unsigned tamDato);
void vaciarPila(tPila *pila);

#endif // PILA_H_INCLUDED
