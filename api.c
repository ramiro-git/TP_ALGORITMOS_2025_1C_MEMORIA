#include "api.h"

void inicializarCargaConfigAPI(tConfigAPI *configAPI)
{
    configAPI->cargado = FALSO;
}

size_t escribirCallBack(void *contenido, size_t tam, size_t ce, void *userp)
{
    size_t tamanioReal = tam * ce;
    tRespuestaAPI *respuesta = (tRespuestaAPI *)userp;
    char *temporal = realloc(respuesta->contenido, respuesta->tamContenido + tamanioReal + 1);

    if (!temporal)
    {
        fprintf(stderr, "Error: realloc fallo en escribirCallBack\n");

        return FALLO_MEMORIA_CALL_BACK;
    }

    respuesta->contenido = temporal;

    mMemcpy(&(respuesta->contenido[respuesta->tamContenido]), contenido,
            tamanioReal);
    respuesta->tamContenido += tamanioReal;
    respuesta->contenido[respuesta->tamContenido] = '\0';

    return tamanioReal;
}

short int llamarAPI(const tConfigAPI *configAPI, const char *metodo,
                    tJson *json)
{
    short int ret;
    long httpCode;
    tRespuestaAPI respuesta;
    char endpoint[TAM_URL_API + TAM_CODIGO_GRUPO - ESPACIO_EXTRA], *auxEndpoint;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers;

    respuesta.contenido = malloc(VERDADERO); /** Esto fue buscado y tomado, ya
    que es un est�ndar (b�sicamente, pide el tama�o m�nimo para un buffer). **/

    if (!respuesta.contenido)
        return FALLO_MEMORIA_CALL_BACK;

    respuesta.tamContenido = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    ret = VERDADERO;

    if (!curl)
        ret = FALLO_INICIALIZACION_API;

    headers = NULL;

    if (ret == VERDADERO)
    {
        if (!mStrcmp(metodo, "POST"))
        {
            snprintf(endpoint, sizeof(endpoint), "%s", configAPI->url);

            auxEndpoint = strrchr(endpoint, '/');

            if (auxEndpoint)
                *auxEndpoint = '\0';
        }
        else if (!mStrcmp(metodo, "GET"))
            snprintf(endpoint, sizeof(endpoint), "%s%s", configAPI->url,
                     configAPI->codigoGrupo);
        else
            ret = FALLO_METODO;

        if (ret == VERDADERO)
        {
            headers = curl_slist_append(headers, "X-Secret: FADSFAS");
            headers = curl_slist_append(headers,
                                        "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, endpoint);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, escribirCallBack);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &respuesta);

            if (!strcmp(metodo, "POST"))
            {
                curl_easy_setopt(curl, CURLOPT_POST, 1L);

                if (json && json->cadena)
                {
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json->cadena);

                    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,
                                     (long)strlen(json->cadena));
                }
            }

            httpCode = 0;

            res = curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

            if (res != CURLE_OK)
            {
                ret = (!mStrcmp(metodo, "POST")) ? FALLO_API_ESCRITURA
                                                 : FALLO_API_LECTURA;
            }
            else if (!mStrcmp(metodo, "POST"))
            {
                if (httpCode == CURLE_OK_SIN_INFORMACION)
                {
                    if (json)
                        json->cadena = strdup("");

                    ret = VERDADERO;
                }
                else
                    ret = FALLO_API_OTRO;
            }
            else
            {
                if (httpCode == CODIGO_OK)
                {
                    if (json)
                        json->cadena = strdup(respuesta.contenido);

                    ret = VERDADERO;
                }
                else if (httpCode == CURLE_OK_SIN_INFORMACION)
                {
                    if (json)
                        json->cadena = strdup("");

                    ret = VERDADERO;
                }
                else if (httpCode == CODIGO_MALA_RESPUESTA)
                {
                    if (json)
                        json->cadena = strdup("");

                    ret = CODIGO_MALA_RESPUESTA;
                }
                else
                    ret = FALLO_API_OTRO;
            }
        }
    }

    free(respuesta.contenido);

    if (curl)
        curl_easy_cleanup(curl);

    if (headers)
        curl_slist_free_all(headers);

    curl_global_cleanup();

    return ret;
}
