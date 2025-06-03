#include "mCtype.h"

#define MAYUSCULA(C) ((C) >= 'A' && (C) <= 'Z')

int tolowerSimple(int c)
{
    return MAYUSCULA(c) ? c + ('a' - 'A') : c;
}
