#ifndef MSTRING_H_INCLUDED
#define MSTRING_H_INCLUDED

#include <stdio.h>
#include "mCtype.h"

char *mStrchr(const char *cadena, int c);
char *mStrrchr(const char *cadena, int c);
char *mStrcpy(char *destino, const char *origen);
void *mMemcpy(void *destino, const void *origen, size_t tam);
void *mMemset(void *destino, int valor, size_t tam);
size_t mStrlen(const char *cadena);
char *mStrcat(char *destino, const char *origen);
int mStrcmp(const char *cadena1, const char *cadena2);

char *mStrchrLower(const char *cadena, int c);

#endif // MSTRING_H_INCLUDED
