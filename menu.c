#include "menu.h"

char menu(const char *mensaje, const char *opciones, const char *mensajeError)
{
    unsigned char error = 0;
    char opcion;

    do
    {
        if (error)
            puts(mensajeError);

        printf("%s", mensaje);
        scanf("%c", &opcion);

        limpiarBufferEntrada();

        error = 1;
    } while (!mStrchrLower(opciones, opcion));

    return opcion;
}
