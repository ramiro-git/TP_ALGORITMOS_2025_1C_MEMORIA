#ifndef JSON_H_INCLUDED
#define JSON_H_INCLUDED

#include "globales.h"
#include "mString.h"
#include <stdlib.h>
#include <ctype.h>

#define VERDADERO 1
#define FALSO 0

#define CAPACIDAD_INICIAL 1024

#define FACTOR_MULTIPLICADOR 2

#define MARGEN_EXTRA_JSON 50
#define MARGEN_ESPECIAL_JSON_ARRAY 5
#define TAM_CADENA_CHAR 2
#define CERRAR_JSON 2

#define MAX_LONGITUD_CADENA 64
#define LONGITUD_MAXIMA_ENTERO 32
#define MAX_LONGITUD_OBJETO_CLAVE 64
#define MAX_LONGITUD_CADENA_GENERICA 128

#define ARRAY_VACIO -33

#define SALTAR_ESPACIOS(cadena)                                                                 \
    while (**(cadena) == ' ' || **(cadena) == '\n' || **(cadena) == '\t' || **(cadena) == '\r') \
    (*(cadena))++

typedef struct
{
    char *cadena;
    size_t cap;
    size_t ce;
} tJson;

typedef void (*ConvertirANumeroFuncion)(void *numero, char *buffer);

tJson *crearJson();
void inicializarJson(tJson *cadenaJson, const char *lectura);
void prefijoElemento(tJson *json);
void prefijoElementoArray(tJson *json);
int hayEspacioSuficiente(tJson *json, size_t nuevaLongitud);
int numeroAJson(tJson *json, const char *key, void *numero,
                ConvertirANumeroFuncion convertir);
int cadenaAJson(tJson *json, const char *clave, const char *valor);
int objetoAJson(tJson *json, const char *clave, tJson *objeto);
int iniciarObjetoAJson(tJson *json, const char *clave);
int cerrarObjetoAJson(tJson *json);
int iniciarArrayAJson(tJson *json, const char *clave);
int elementoEnArrayAJson(tJson *json, const char *valorComoTexto);
int numeroEnArrayAJson(tJson *json, void *numero,
                       ConvertirANumeroFuncion convertir);
int cadenaEnArrayAJson(tJson *json, const char *valor);
int cerrarArrayAJson(tJson *json);
void cerrarJson(tJson *json);
void destruirJson(tJson *json);

int esArrayVacio(tJson *json);

int parsearCadena(char **cadena, char *destino);
int parsearNumero(char **input, unsigned *numero);
int parsearArray(char **input);
int parsearObjeto(char **input);
int parsearValor(char **input);

#endif // JSON_H_INCLUDED
