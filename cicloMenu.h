#ifndef CICLOMENU_H_INCLUDED
#define CICLOMENU_H_INCLUDED

#include "globales.h"
#include "menu.h"
#include "manejoArchivos.h"
#include "manejoCadenas.h"
#include "api.h"
#include "jugar.h"
#include "ranking.h"
#include <unistd.h>

int cicloMenu();

int mostrarRanking(tConfigAPI *configAPI);

#endif // CICLOMENU_H_INCLUDED
