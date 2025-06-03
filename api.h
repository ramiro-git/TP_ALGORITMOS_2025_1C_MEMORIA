#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include "globales.h"
#include "json.h"
#include "mString.h"
#include "curl/curl.h"

#define FALLO_INICIALIZACION_API -9
#define FALLO_API_LECTURA -99
#define FALLO_API_ESCRITURA -999
#define FALLO_API_OTRO -9999
#define FALLO_METODO -8
#define FALLO_MEMORIA_CALL_BACK 0

#define CODIGO_OK 200
#define CURLE_OK_SIN_INFORMACION 204
#define CODIGO_MALA_RESPUESTA 400

typedef struct
{
    char *contenido;
    size_t tamContenido;
} tRespuestaAPI;

void inicializarCargaConfigAPI(tConfigAPI *configAPI);
size_t writeCallBack(void *contents, size_t size, size_t nmemb, void *userp);
short int llamarAPI(const tConfigAPI *configAPI, const char *metodo,
                    tJson *json);

#endif // API_H_INCLUDED
