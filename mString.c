#include "mString.h"

char *mStrchr(const char *cadena, int c)
{
    while (*cadena && *(char *)cadena != (char)c)
        ((char *)cadena++);

    return *(char *)cadena == (char)c ? (char *)cadena : NULL;
}

char *mStrrchr(const char *cadena, int c)
{
    char *puntero = NULL;

    while (*cadena)
    {
        if (*cadena == c)
            puntero = (char *)cadena;

        cadena++;
    }

    return puntero;
}

char *mStrcpy(char *destino, const char *origen)
{
    char *auxDestino = destino;

    while ((*destino++ = *(char *)origen++) != '\0')
        ;

    return auxDestino;
}

void *mMemcpy(void *destino, const void *origen, size_t tam)
{
    void *auxDestino = destino;

    while (tam--)
        *((char *)destino++) = *((char *)origen++);

    return auxDestino;
}

void *mMemset(void *destino, int valor, size_t tam)
{
    void *auxDestino = destino;

    while (tam--)
        *((char *)destino++) = (char)valor;

    return auxDestino;
}

size_t mStrlen(const char *cadena)
{
    size_t contador = 0;

    while (*((char *)cadena++))
        contador++;

    return contador;
}

char *mStrcat(char *destino, const char *origen)
{
    char *auxDestino = destino;

    while (*destino)
        destino++;

    while ((*destino++ = *(char *)origen++) != '\0')
        ;

    return auxDestino;
}

int mStrcmp(const char *cadena1, const char *cadena2)
{
    while (*cadena1 && *cadena1 == *cadena2)
    {
        cadena1++;
        cadena2++;
    }

    return *(unsigned char *)cadena1 - *(unsigned char *)cadena2;
}

char *mStrchrLower(const char *cadena, int c)
{
    while (*cadena)
    {
        if (tolowerSimple(*cadena) == tolowerSimple(c))
            return (char *)cadena;

        cadena++;
    }

    return NULL;
}
