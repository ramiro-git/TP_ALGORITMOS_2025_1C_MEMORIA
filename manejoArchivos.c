#include "manejoArchivos.h"

int verificarArchivoLeido(tConfigAPI *configAPI,
                          const char *nombreArchivo,
                          const char *modoApertura)
{
    if (configAPI->cargado)
        return VERDADERO;

    if (!leerArchivoConfigAPI(nombreArchivo, modoApertura, configAPI->url,
                              configAPI->codigoGrupo))
    {
        fprintf(stderr, "Error al leer %s\n", nombreArchivo);

        return FALSO;
    }

    configAPI->cargado = VERDADERO;

    return VERDADERO;
}

unsigned char leerArchivoConfigAPI(const char *nombreArchivo,
                                   const char *modoApertura,
                                   char *urlAPI,
                                   char *codigoGrupo)
{
    char linea[TAM_URL_API + TAM_CODIGO_GRUPO + ESPACIOS_DEL_MEDIO];
    FILE *archivo = fopen(nombreArchivo, modoApertura);

    if (!archivo)
        return FALSO;

    if (fgets(linea, TAM_URL_API + TAM_CODIGO_GRUPO + ESPACIOS_DEL_MEDIO,
              archivo))
    {
        if (!parsearConfigAPI(linea, urlAPI, codigoGrupo))
        {
            fclose(archivo);

            return FALSO;
        }
    }
    else
    {
        fclose(archivo);

        return FALSO;
    }

    fclose(archivo);

    return VERDADERO;
}

char *generarNombreArchivo()
{
    static char nombreArchivo[LONGITUD_CARACTERES_ARCHIVO_INFORME];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    strftime(nombreArchivo, sizeof(nombreArchivo),
             "informe-juego_%Y-%m-%d-%H-%M.txt", tm_info);

    return nombreArchivo;
}

void escribirSalida(FILE *archivo, const char *formato, ...)
{
    va_list args;
    va_start(args, formato);
    vfprintf(archivo, formato, args);
    va_end(args);
}
