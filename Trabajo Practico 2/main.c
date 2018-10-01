#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utn.h"

#define CANTIDAD_EMPLEADOS 50
int main()
{
     empleadoDes empleados [CANTIDAD_EMPLEADOS];
     initEmployees(empleados, CANTIDAD_EMPLEADOS);
     mostrarMenu (empleados, CANTIDAD_EMPLEADOS);
    return 0;
}
