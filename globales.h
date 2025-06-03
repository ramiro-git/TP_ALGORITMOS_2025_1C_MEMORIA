#ifndef GLOBALES_H_INCLUDED
#define GLOBALES_H_INCLUDED

#define VERDADERO 1
#define FALSO 0

#define TAM_URL_API 51
#define TAM_CODIGO_GRUPO 8
#define ESPACIOS_DEL_MEDIO 4
#define ESPACIO_EXTRA 1
#define TAM_NOMBRE_JUGADOR 20

#define FALLO_MEMORIA -1
#define FALLO_LECTURA -2
#define FALLO_ESCRITURA -3

#define FACTOR_INCREMENTO 2

#define ARCHIVO_API "configAPI.txt"

#define CONSTANTE_LECTURA "rt"
#define CONSTANTE_ESCRITURA "wt"

#define LONGITUD_CARACTERES_ARCHIVO_INFORME 35

#define TIEMPO_ESPERA 3

#define TEXTO_OPCION_INVALIDA "\n\nOpcion invalida, intente de nuevo\n"

typedef struct
{
    char url[TAM_URL_API];
    char codigoGrupo[TAM_CODIGO_GRUPO];
    unsigned char cargado;
} tConfigAPI;

#endif // GLOBALES_H_INCLUDED
