//#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    int retorno = -1;
    pArchivo = fopen(path,"r");
    if(!parser_EmployeeFromText(pArchivo, pArrayListEmployee))
    {
        retorno = 0;
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    int retorno = -1;
    pArchivo = fopen(path,"rb");
    if(!parser_EmployeeFromBinary(pArchivo, pArrayListEmployee))
    {
        retorno = 0;
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    char bufferNombre[128];
    int bufferHorasTrabajo;
    int bufferSueldo;
    int bufferId;
    Employee* newEmployee;
    if (pArrayListEmployee != NULL)
    {
        newEmployee = Employee_new();
        if( newEmployee != NULL &&
           utn_getNombre(bufferNombre, 128, "Ingrese Nombre del empleado\n", "Nombre invalido\n",3) == 0&&
           utn_getEntero(&bufferHorasTrabajo,10,"Ingrese Horas trabajadas\n", "Horas invalidas\n", 3) == 0&&
           utn_getEntero(&bufferSueldo,10,"Ingrese Sueldo\n", "Sueldo Invalido\n", 3) == 0)
        {
            bufferId = getNextId(pArrayListEmployee);
            Employee_setId(newEmployee,bufferId);
            Employee_setNombre(newEmployee,bufferNombre);
            Employee_setHorasTrabajadas(newEmployee, bufferHorasTrabajo);
            Employee_setSueldo(newEmployee, bufferSueldo);
            ll_add(pArrayListEmployee, newEmployee);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int id;
   //__fpurge(stdin);
    if (pArrayListEmployee != NULL &&
        utn_getEntero(&id, 10, "Ingrese id\n", "id invalido\n", 3) == 0
        && Employee_BuscarPorId (pArrayListEmployee, id)== 0)
    {
      retorno = 0;
    }

    return retorno;
}


/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    int id;
    int bufferId;
    int bufferHoras;
    int bufferSueldo;
    char resp;
    char bufferNombre[128];
    Employee * auxPunteroEmpleado;
    if (pArrayListEmployee != NULL &&
        utn_getEntero(&id, 10, "Ingrese Id\n", "Id invalido", 3) == 0)
    {
        for (i = 1; i< ll_len(pArrayListEmployee); i++)
        {
            auxPunteroEmpleado = ll_get(pArrayListEmployee,i);
            Employee_getId(auxPunteroEmpleado,&bufferId);
            if(bufferId == id)
            {
                 Employee_getNombre(auxPunteroEmpleado, bufferNombre);
                 Employee_getHorasTrabajadas(auxPunteroEmpleado, &bufferHoras);
                 Employee_getSueldo(auxPunteroEmpleado,&bufferSueldo);
                 printf("\nEl empleado es %s - horas Trabajdas: %d - Sueldo: %d\n", bufferNombre, bufferHoras, bufferSueldo);
                 printf("Desea eliminar empleado Y/N\n");
                 scanf("%c", &resp);
                 if(resp == 'Y')
                 {
                   Employee_delete(auxPunteroEmpleado);
                   ll_remove(pArrayListEmployee,i);
                   retorno = 0;
                   break;
                 }else
                 {
                     break;
                 }
            }
        }
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    Employee* auxPunteroEmpleado;
    char nombre[1024];
    int id;
    int bufferHorasTrabajo;
    int bufferSueldo;
    if(pArrayListEmployee != NULL)
    {
        for (i = 0; i< ll_len(pArrayListEmployee); i++)
        {
             auxPunteroEmpleado = ll_get(pArrayListEmployee,i);
             Employee_getNombre(auxPunteroEmpleado,nombre);
             Employee_getId(auxPunteroEmpleado, &id);
             Employee_getHorasTrabajadas(auxPunteroEmpleado, &bufferHorasTrabajo);
             Employee_getSueldo(auxPunteroEmpleado, &bufferSueldo);
             printf("\nId %d - Nombre: %s - Horas: %d - Sueldo: %d \n",id, nombre, bufferHorasTrabajo, bufferSueldo);
             retorno = 0;
        }
    }

    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int resp;
    do
    {
        printf("1. Ordenar por id\n");
        printf("2. Ordenar por nombre\n");
        printf("3. Volver a Menu Principal\n");
        scanf("%d", &resp);
        switch(resp)
        {
            case 1:
            ll_sort(pArrayListEmployee, Employee_sortById, 1);
            controller_ListEmployee(pArrayListEmployee);
            resp = 3;
            break;
            case 2:
            ll_sort(pArrayListEmployee,employee_criterioSortNombre,1);
            controller_ListEmployee(pArrayListEmployee);
            resp = 3;
            break;
            case 3:
            break;
            default:
            printf("Opcion no valida");
            break;
        }
        retorno = 0;
    }while (resp != 3);
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE* pArchivo = fopen(path,"w+");
    Employee* pEmpleado = NULL;
    int i;
    char bufferNombre[1024];
    int bufferId;
    int bufferHorasTrabajadas;
    int bufferSueldo;
   if(pArchivo != NULL && pArrayListEmployee != NULL)
    {
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            if(i==0)
            {
                fprintf(pArchivo,"id,nombre,horas,sueldo\n");
            }
            pEmpleado = ll_get(pArrayListEmployee,i);
            Employee_getNombre(pEmpleado,bufferNombre);
            Employee_getHorasTrabajadas(pEmpleado,&bufferHorasTrabajadas);
            Employee_getSueldo(pEmpleado,&bufferSueldo);
            Employee_getId(pEmpleado,&bufferId);
            fprintf(pArchivo,"%d,%s,%d,%d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            retorno = 0;
        }
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE *pArchivo = fopen(path,"wb");
    int i;
    Employee * auxPunteroEmployee;
    if(pArchivo != NULL)
    {
        for(i=0; i< ll_len(pArrayListEmployee); i++)
        {
            auxPunteroEmployee = ll_get(pArrayListEmployee,i);
            fwrite(auxPunteroEmployee,sizeof(Employee), 1, pArchivo);
            retorno = 0;
        }
    }
    fclose(pArchivo);
    return retorno;
}

void controller_mostratMenu()
{
    int option;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
        printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
        printf("2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n");
        printf("3. Alta de empleado\n");
        printf("4. Modificar datos de empleado\n");
        printf("5. Baja de empleado\n");
        printf("6. Listar empleados\n");
        printf("7. Ordenar empleados\n");
        printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
        printf("9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n");
        printf("10. Salir\n");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
            printf("\nSize de la lista %d", ll_len(listaEmpleados));
            controller_loadFromText("data.csv",listaEmpleados);
            printf("\nSize de la lista %d\n", ll_len(listaEmpleados));
            break;
            case 2:
            controller_loadFromBinary("data.bin",listaEmpleados);
            break;
            case 3:
            if (controller_addEmployee(listaEmpleados)== 0)
            {
                printf("Empleado Agregado\n");
            }
            break;
            case 4:
            if(controller_editEmployee(listaEmpleados)==0)
            {
                printf("Empleado modificado\n");
            }else
            {
                printf("No existe ID");
            }
            break;
            case 5:
            if (controller_removeEmployee(listaEmpleados)== 0)
            {
                printf("Empleado Borrado\n");
            }
            break;
            case 6:
            controller_ListEmployee(listaEmpleados);
            break;
            case 7:
            controller_sortEmployee(listaEmpleados);
            break;
            case 8:
            if (controller_saveAsText("data.csv", listaEmpleados) == 0)
            {
                printf("\nSe guardo lista existosamente\n");
            }else
            {
                printf("No hay ninguna lista cargada\n");
            }
            break;
            case 9:
            controller_saveAsBinary("data.bin", listaEmpleados);
            break;
            case 10:
            printf("salio\n");
            break;
            default:
            printf("Opcion no valida\n");
            break;
        }
    }while(option != 10);
}
