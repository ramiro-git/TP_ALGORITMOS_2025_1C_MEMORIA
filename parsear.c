#include "parsear.h"

unsigned char parsearConfigAPI(char *linea, char *urlAPI, char *codigoGrupo)
{
    char *aux = mStrchr(linea, '\n');

    if (!aux)
        return FALSO;

    *aux = '\0';

    aux = mStrrchr(linea, '|');

    mStrcpy(codigoGrupo, aux + 2);

    *(aux - 1) = '\0';

    mStrcpy(urlAPI, linea);

    return VERDADERO;
}
