#include "manejoCadenas.h"

char pedirOpcion(const char *opciones, const char *validas)
{
    char resultado;

    system("cls");

    resultado = tolowerSimple(menu(opciones, validas, TEXTO_OPCION_INVALIDA));

    system("cls");

    return resultado;
}

void pedirNombre(char *nombreJugador, unsigned tamNombreJugador)
{
    unsigned i;

    printf("Ingresar nombre de jugador: ");
    fflush(stdin);
    fgets(nombreJugador, tamNombreJugador, stdin);

    i = 0;

    while (*(nombreJugador + i))
    {
        if (*(nombreJugador + i) == '\n')
            *(nombreJugador + i) = '\0';
        else
            i++;
    }
    system("cls");
}

void convertirUnsignedCharACadena(void *numero, char *buffer)
{
    sprintf(buffer, "%d", *(unsigned char *)numero);
}

const char *efectoTexto(unsigned char efecto)
{
    switch (efecto)
    {
    case EFECTO_NORMAL:
        return "Normal";
    case EFECTO_REPETIR:
        return "Repetir turno";
    case EFECTO_ESPEJO:
        return "Espejo";
    case EFECTO_SACAR_PUNTOS:
        return "Sacar Puntos";
    default:
        return "Vacio";
    }
}

void limpiarBufferEntrada(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
