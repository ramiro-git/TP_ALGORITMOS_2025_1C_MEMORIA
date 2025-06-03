#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "mString.h"
#include <stdio.h>
#include <stdlib.h>

#define VERDADERO 1
#define FALSO 0

#define FALLO_MEMORIA -1

#define LISTA_VACIA -2

#define ELEMENTO_DUPLICADO -3

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *siguiente;
} tNodo;

typedef tNodo *tLista;

typedef void (*Mostrar)(const void *, FILE *);
typedef int (*tAcumular)(void **, unsigned *, const void *, unsigned);
typedef int (*tComparar)(const void *, const void *);

void crearLista(tLista *lista);
int ponerEnOrden(tLista *lista, const void *dato, unsigned tamDato,
                 tComparar comparar, tAcumular acumular,
                 unsigned char duplicados);
void vaciarListaYMostrar(tLista *lista, Mostrar mostrar, FILE *archivo);

#endif // LISTA_H_INCLUDED
