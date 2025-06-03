#ifndef MANEJOARCHIVOS_H_INCLUDED
#define MANEJOARCHIVOS_H_INCLUDED

#include "parsear.h"
#include "api.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define VERDADERO 1
#define FALSO 0

int verificarArchivoLeido(tConfigAPI *configAPI,
                          const char *nombreArchivo,
                          const char *modoApertura);

unsigned char leerArchivoConfigAPI(const char *nombreArchivo,
                                   const char *modoApertura,
                                   char *urlAPI,
                                   char *codigoGrupo);

char *generarNombreArchivo();
void escribirSalida(FILE *archivo, const char *formato, ...);

#endif // MANEJOARCHIVOS_H_INCLUDED
