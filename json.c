#include "json.h"

tJson *crearJson()
{
    tJson *cadenaJson = (tJson *)malloc(sizeof(tJson));

    if (!cadenaJson)
        return NULL;

    cadenaJson->cadena = (char *)malloc(CAPACIDAD_INICIAL * sizeof(char));

    if (!cadenaJson->cadena)
    {
        free(cadenaJson);

        return NULL;
    }

    cadenaJson->cap = CAPACIDAD_INICIAL;
    cadenaJson->ce = 0;

    return cadenaJson;
}

void inicializarJson(tJson *json, const char *lectura)
{
    if (lectura && !mStrcmp(lectura, "r"))
    {
        if (json && json->cadena)
            mStrcpy(json->cadena, "");
    }
    else
    {
        if (json && json->cadena)
            mStrcpy(json->cadena, "{\n");
    }
}

void prefijoElemento(tJson *json)
{
    if (json->ce > 0)
        mStrcat(json->cadena, ",\n");
}

void prefijoElementoArray(tJson *json)
{
    if (json->ce > 0)
        mStrcat(json->cadena, ",\n");
}

int hayEspacioSuficiente(tJson *json, size_t nuevaLongitud)
{
    size_t nuevaCap = json->cap * FACTOR_INCREMENTO;
    void *nuevoJson;

    if (nuevaLongitud >= json->cap)
    {
        while (nuevaCap <= nuevaLongitud)
            nuevaCap *= FACTOR_MULTIPLICADOR;

        nuevoJson = realloc(json->cadena, nuevaCap);

        if (!nuevoJson)
            return FALSO;

        json->cadena = nuevoJson;
        json->cap = nuevaCap;
    }

    return VERDADERO;
}

int numeroAJson(tJson *json, const char *clave, void *numero,
                ConvertirANumeroFuncion convertir)
{
    char buffer[MAX_LONGITUD_CADENA];
    size_t espacioRequerido = mStrlen(json->cadena) + mStrlen(clave) +
                              mStrlen(buffer) + MARGEN_EXTRA_JSON;

    convertir(numero, buffer);

    if (!hayEspacioSuficiente(json, espacioRequerido))
        return FALLO_MEMORIA;

    prefijoElemento(json);

    mStrcat(json->cadena, "  \"");
    mStrcat(json->cadena, clave);
    mStrcat(json->cadena, "\": ");
    mStrcat(json->cadena, buffer);

    json->ce++;

    return VERDADERO;
}

int cadenaAJson(tJson *json, const char *clave, const char *valor)
{
    size_t espacioRequerido = mStrlen(json->cadena) + mStrlen(clave) +
                              mStrlen(valor) + MARGEN_EXTRA_JSON;

    if (!hayEspacioSuficiente(json, espacioRequerido))
        return FALLO_MEMORIA;

    prefijoElemento(json);

    mStrcat(json->cadena, "  \"");
    mStrcat(json->cadena, clave);
    mStrcat(json->cadena, "\": \"");
    mStrcat(json->cadena, valor);
    mStrcat(json->cadena, "\"");

    json->ce++;

    return VERDADERO;
}

int objetoAJson(tJson *json, const char *clave, tJson *objeto)
{
    char temp[TAM_CADENA_CHAR];
    const char *punteroObjetoCadena = objeto->cadena;
    size_t espacioRequerido = mStrlen(json->cadena) + mStrlen(clave) +
                              mStrlen(objeto->cadena) + MARGEN_EXTRA_JSON;

    if (!hayEspacioSuficiente(json, espacioRequerido))
        return FALLO_MEMORIA;

    prefijoElemento(json);

    mStrcat(json->cadena, "  \"");
    mStrcat(json->cadena, clave);
    mStrcat(json->cadena, "\":\n  ");

    while (*punteroObjetoCadena)
    {
        if (*punteroObjetoCadena == '\n')
        {
            mStrcat(json->cadena, "\n  ");

            punteroObjetoCadena++;
        }
        else
        {
            *temp = *punteroObjetoCadena;
            *(temp + 1) = '\0';

            mStrcat(json->cadena, temp);

            punteroObjetoCadena++;
        }
    }

    json->ce++;

    return VERDADERO;
}

int iniciarObjetoAJson(tJson *json, const char *clave)
{
    size_t req = mStrlen(json->cadena) + mStrlen(clave) + MARGEN_EXTRA_JSON;

    if (!hayEspacioSuficiente(json, req))
        return FALLO_MEMORIA;

    prefijoElemento(json);

    mStrcat(json->cadena, "  \"");
    mStrcat(json->cadena, clave);
    mStrcat(json->cadena, "\": {\n");

    return VERDADERO;
}

int cerrarObjetoAJson(tJson *json)
{
    if (!hayEspacioSuficiente(json, mStrlen(json->cadena) + MARGEN_ESPECIAL_JSON_ARRAY))
        return FALLO_MEMORIA;

    mStrcat(json->cadena, "\n  }");

    return VERDADERO;
}

int iniciarArrayAJson(tJson *json, const char *clave)
{
    size_t req = mStrlen(json->cadena) + mStrlen(clave) + MARGEN_EXTRA_JSON;

    if (!hayEspacioSuficiente(json, req))
        return FALLO_MEMORIA;

    prefijoElemento(json);

    mStrcat(json->cadena, "  \"");
    mStrcat(json->cadena, clave);
    mStrcat(json->cadena, "\": [\n");

    json->ce = 0;

    return VERDADERO;
}

int elementoEnArrayAJson(tJson *json, const char *valorComoTexto)
{
    size_t req = mStrlen(json->cadena) + mStrlen(valorComoTexto) + MARGEN_EXTRA_JSON;

    if (!hayEspacioSuficiente(json, req))
        return FALLO_MEMORIA;

    prefijoElementoArray(json);

    mStrcat(json->cadena, "    ");
    mStrcat(json->cadena, valorComoTexto);

    json->ce++;

    return VERDADERO;
}

int numeroEnArrayAJson(tJson *json, void *numero,
                       ConvertirANumeroFuncion convertir)
{
    char buf[MAX_LONGITUD_CADENA];

    convertir(numero, buf);

    return elementoEnArrayAJson(json, buf);
}

int cadenaEnArrayAJson(tJson *json, const char *valor)
{
    char buf[MAX_LONGITUD_CADENA + TAM_CADENA_CHAR];

    snprintf(buf, sizeof(buf), "\"%s\"", valor);

    return elementoEnArrayAJson(json, buf);
}

int cerrarArrayAJson(tJson *json)
{
    if (!hayEspacioSuficiente(json, mStrlen(json->cadena) + MARGEN_ESPECIAL_JSON_ARRAY))
        return FALLO_MEMORIA;

    mStrcat(json->cadena, "\n  ]");

    return VERDADERO;
}

void cerrarJson(tJson *json)
{
    size_t longitudCadena = mStrlen(json->cadena);

    if (longitudCadena > 0 &&
        json->cadena[longitudCadena - CERRAR_JSON] == ',' &&
        json->cadena[longitudCadena - 1] == '\n')
        json->cadena[longitudCadena - CERRAR_JSON] = '\0';

    mStrcat(json->cadena, "\n}");
}

void destruirJson(tJson *json)
{
    if (json->cadena)
        free(json->cadena);

    if (json)
        free(json);
}

int esArrayVacio(tJson *json)
{
    char *cursor;

    if (!json || !json->cadena)
        return FALSO;

    cursor = json->cadena;

    SALTAR_ESPACIOS(&cursor);

    if (*cursor != '[')
        return FALSO;

    cursor++;

    SALTAR_ESPACIOS(&cursor);

    if (*cursor != ']')
        return FALSO;

    cursor++;

    SALTAR_ESPACIOS(&cursor);

    return *cursor == '\0';
}

int parsearCadena(char **cadena, char *destino)
{
    if (**cadena != '"')
        return FALSO;

    (*cadena)++;

    while (**cadena && **cadena != '"')
    {
        *destino++ = **cadena;

        (*cadena)++;
    }

    if (**cadena != '"')
        return FALSO;

    *destino = '\0';

    (*cadena)++;

    return VERDADERO;
}

int parsearNumero(char **input, unsigned *numero)
{
    char buffer[LONGITUD_MAXIMA_ENTERO];
    unsigned i = 0;

    while (**input && (isdigit(**input) || **input == '-'))
    {
        buffer[i++] = **input;

        (*input)++;
    }

    buffer[i] = '\0';

    *numero = atoi(buffer);

    return VERDADERO;
}

int parsearArray(char **input)
{
    if (**input != '[')
        return FALSO;

    (*input)++;

    printf("Array [\n");

    SALTAR_ESPACIOS(input);

    while (**input && **input != ']')
    {
        parsearValor(input);

        SALTAR_ESPACIOS(input);

        if (**input == ',')
        {
            (*input)++;

            SALTAR_ESPACIOS(input);
        }
    }

    if (**input != ']')
        return FALSO;

    (*input)++;

    printf("] Fin array\n");

    return VERDADERO;
}

int parsearObjeto(char **input)
{
    char clave[MAX_LONGITUD_OBJETO_CLAVE];

    if (**input != '{')
        return FALSO;

    (*input)++;

    printf("Objeto {\n");

    SALTAR_ESPACIOS(input);

    while (**input && **input != '}')
    {
        if (!parsearCadena(input, clave))
            return FALSO;

        SALTAR_ESPACIOS(input);

        if (**input != ':')
            return FALSO;

        (*input)++;

        SALTAR_ESPACIOS(input);

        printf("Clave: %s => ", clave);

        parsearValor(input);

        SALTAR_ESPACIOS(input);

        if (**input == ',')
        {
            (*input)++;

            SALTAR_ESPACIOS(input);
        }
    }

    if (**input != '}')
        return FALSO;

    (*input)++;

    printf("} Fin objeto\n");

    return VERDADERO;
}

int parsearValor(char **input)
{
    char cadena[MAX_LONGITUD_CADENA_GENERICA];
    unsigned numero;

    SALTAR_ESPACIOS(input);

    if (**input == '"')
    {
        if (!parsearCadena(input, cadena))
            return FALSO;

        printf("Cadena: \"%s\"\n", cadena);
    }
    else if (isdigit(**input) || **input == '-')
    {
        if (!parsearNumero(input, &numero))
            return FALSO;

        printf("Numero: %d\n", numero);
    }
    else if (**input == '{')
        return parsearObjeto(input);
    else if (**input == '[')
        return parsearArray(input);
    else
    {
        printf("Valor desconocido: '%c'\n", **input);

        return FALSO;
    }

    return VERDADERO;
}
