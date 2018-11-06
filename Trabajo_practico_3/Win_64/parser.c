#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    char bufferId[1024];
    char bufferNombre[1024];
    char bufferHorasTrabajadas[1024];
    char bufferSueldo[1024];
    Employee * pEmpleado;
    int flagOnce = 1;
    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            if(flagOnce)
            {
                flagOnce = 0;
                fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",
                        bufferId,
                        bufferNombre,
                        bufferHorasTrabajadas,
                        bufferSueldo);

            }
            fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",
                        bufferId,
                        bufferNombre,
                        bufferHorasTrabajadas,
                        bufferSueldo);
            pEmpleado = Employee_newConParametros( bufferId,
                                        bufferNombre,
                                        bufferHorasTrabajadas,
                                        bufferSueldo);
            if(pEmpleado != NULL)
            {
                retorno = 0;
                ll_add(pArrayListEmployee, pEmpleado);

            }
        }
    }
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{

    int retorno = -1;
    Employee * pEmpleado;
    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            pEmpleado = Employee_new();
            fread(pEmpleado, sizeof(Employee), 1, pFile);
            ll_add(pArrayListEmployee,pEmpleado);
        }
        retorno = 0;
    }
    return retorno;
}

