#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utn.h"
/**
* \brief    Inciializa el array en 0 para indicar
*           que esta vacio.
* \param pArray Es el array que se recorre
* \param limite Es el limite de empleados que puede guardar el array
* \return El retorno es 0 si se vacio el array, si no el retorno es -1.
*/
int initEmployees(empleadoDes* pArray, int limite)
{
	int retorno = -1;
	if(pArray != NULL && limite > 0)
	{
		for (int i = 0; i <= limite; i++)
		{
			pArray[i].isEmpty = 0;
			retorno = 0;
		}
	}
	return retorno;
}
/**
* \brief Evalua si se trata de un float
* \param pBuffer Es la cadena que evaluamos
* \param limite Es el numero maximo de cifras
* \return En caso de exito retorna 1, si no 0
*/
static int isValidFloat(char *pBuffer, int limite)
{
    int retorno = 0;
    int i;
    int contadorDePuntos = 0;
    if  ((pBuffer != NULL && limite > 0 ) &&
        (((pBuffer[0] == '-' || pBuffer[0] == '+') && pBuffer[1] != '.') ||
        (pBuffer[0]>='0' && pBuffer[0]<='9')))
    {
        retorno = 1;
        for(i=1;i < limite && pBuffer[i] != '\0';i++)
        {
            if(pBuffer[i]=='.' && contadorDePuntos==0)
            {
                contadorDePuntos++;
            }
            else if (!(pBuffer[i]>='0' && pBuffer[i]<='9'))
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
/**
* \brief Evalua si se trata de un entero
* \param pBuffer Es la cadena que evaluamos
* \param limite Es el numero maximo de cifras
* \return En caso de exito retorna 1, si no 0
*
*/
static int isValidEntero(char *pBuffer, int limite)
{
    int retorno = 0;
    int i;
    if  ((pBuffer != NULL && limite > 0 ) &&
        (pBuffer[0] == '-' || pBuffer[0] == '+' ||
        (pBuffer[0]>='0' && pBuffer[0]<='9')))
    {
        retorno = 1;
        for(i=1;i < limite && pBuffer[i] != '\0';i++)
        {
            if (!(pBuffer[i]>='0' && pBuffer[i]<='9'))
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
/**
* \brief    Evalua si es un nombre valido
* \param pBuffer Es la cadena que evaluamos
* \param limite Es el tamano maximo del string
* \return En caso de exito retorna 1, si no 0
*/
static int utn_isValidNombre(char* pBuffer,int limite)
{
    int retorno = 0;
    int i;
    if(pBuffer != NULL && limite > 0)
    {
        retorno = 1;
        for(i=0;i < limite && pBuffer[i] != '\0';i++)
        {
            if(tolower(pBuffer[i]) < 'a' || tolower(pBuffer[i]) > 'z')
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
/**
* \brief El usuario ingresa una cadena con fgets
* \param pBuffer Recibe el texto ingresado en caso de exito
* \param limite Es el tamano maximo del string
* \return En caso de exito retorna 0, si no -1
*/
static int utn_getString(char* pBuffer, int limite)
{
    int retorno = -1;
    char bufferStr[4096];
    int len;
    if(pBuffer != NULL && limite > 0)
    {
        //__fpurge(stdin);
        fflush(stdin);
        fgets(bufferStr,limite,stdin);
        len = strlen(bufferStr);
        if(len != limite-1 ||  bufferStr[limite-2] == '\n')
        {
            bufferStr[len-1] = '\0';
        }
        retorno = 0;
        strncpy(pBuffer,bufferStr,limite);
    }
    return retorno;
}
/**
* \brief    Toma la cadena y evalua si es un nombre
* \param pNombre Recibe el texto ingresado en caso de exito
* \param limite Es el tamano maximo del string
* \param msg Es el mensaje que se muestra al usuario antes de introducir datos
* \param msgErr Es el mensaje que se muestra en caso de error
* \param reintentos Veces que el usuario podra volver a introducir el dato
* \return En caso de exito retorna 0, si no -1
*/
int utn_getNombre(  char* pNombre,int limite, char* msg, char* msgErr, int reintentos)
{
    int retorno=-1;
    char bufferNombre[4096];
    if(pNombre != NULL && limite > 0 && msg != NULL && msgErr != NULL && reintentos >= 0 )
    {
      do
      {
         reintentos--;
         printf("%s", msg);
         if (utn_getString(bufferNombre, limite) == 0 && utn_isValidNombre(bufferNombre, limite))
         {
            strncpy(pNombre, bufferNombre, limite);
            retorno = 0;
            break;
         }else
         {
            printf("%s", msgErr);
         }


      }while(reintentos>=0);
    }
    return retorno;
}
/**
* \brief    Toma la cadena y evalua si es un float en caso de exito lo transforma a float
* \param pFloat Recibe el numero ingresado en caso de exito
* \param limite Es el tamano maximo de cifras
* \param mensaje Es el mensaje que se muestra al usuario antes de introducir datos
* \param mensajeError Es el mensaje que se muestra en caso de error
* \param reintentos Veces que el usuario podra volver a introducir el dato
* \return En caso de exito retorna 0, si no -1
*/
int utn_getFloat(   float *pFloat, int limite, char *mensaje,char *mensajeError, int reintentos)
{
    int retorno=-1;
    char bufferFloat[4096];
    if( pFloat != NULL && limite > 0 && mensaje != NULL &&mensajeError != NULL && reintentos>=0)
    {
        do
        {
            reintentos--;
            printf("\n%s", mensaje);
            if( utn_getString(bufferFloat, limite) == 0 &&
                isValidFloat(bufferFloat, limite))
            {
                *pFloat = atof(bufferFloat);
                retorno = 0;
                break;
            }
            else
            {
                printf("\n%s", mensajeError);
            }
        }while(reintentos>=0);
    }
    return retorno;
}
/**
* \brief    Toma la cadena y evalua si es un entero en caso de exito lo transforma a entero
* \param pEntero Recibe el numero ingresado en caso de exito
* \param limite Es el tamano maximo de cifras
* \param mensaje Es el mensaje que se muestra al usuario antes de introducir datos
* \param mensajeError Es el mensaje que se muestra en caso de error
* \param reintentos Veces que el usuario podra volver a introducir el dato
* \return En caso de exito retorna 0, si no -1
*/
int utn_getEntero(  int *pEntero, int limite, char *mensaje,char *mensajeError, int reintentos)
{
    int retorno=-1;
    char bufferEntero[4096];
    if( pEntero != NULL && limite > 0 && mensaje != NULL &&
        mensajeError != NULL && reintentos>=0)
    {
        do
        {
            reintentos--;
            printf("\n%s", mensaje);
            if( utn_getString(bufferEntero, limite) == 0 &&
                isValidEntero(bufferEntero, limite))
            {
                *pEntero = atoi(bufferEntero);
                retorno = 0;
                break;
            }
            else
            {
                printf("\n%s", mensajeError);
            }
        }while(reintentos>=0);
    }
    return retorno;
}
/**
* \brief    Toma la cadena e imprime lo que tenga guardado
* \param pArray Recibe el array ingresado
* \param limite Es el tamano maximo del string
*/
void printProducto(empleadoDes* pArray, int len)
{
      if (pArray != NULL && len > 0)
      {
      	for (int i =0; i< len; i++ )
		{
			if(pArray[i].isEmpty == 1)
            {
                printf("Id %d\n", pArray[i].id);
                printf("Nombre %s\n", pArray[i].name);
                printf("apellido %s\n", pArray[i].lastName);
                printf("Salario %f\n", pArray[i].salary);
                printf("Sector %d\n", pArray[i].sector);
                printf("---------------------------------\n");                }
        }
      }
}
/**
* \brief    evalua el id ingresado y en caso de exito te permite
*           modificar la informacion
* \param pArray Recibe el array ingresado
* \param id es el numero a buscar
* \param limite Es el tamano maximo del string
*/
int utn_getEmpleadoModificar(empleadoDes* pArray, int len, int id)
{
    int retorno = -1;
    int resp;
    char bufferNombre[51];
    char bufferApellido[51];
    float bufferSalario;
    int bufferSector;
    if(pArray != NULL && len > 0 && len>0 && id >= 0 && id < len )
    {
        if (pArray[id].isEmpty == 1)
        {
            printf("\n Desea modificar : \n 1-Nombre: \n 2-Apellido: \n 3-Salario: \n 4 Sector: \n 5-Salir \n");
            scanf("%d",&resp);
            switch(resp)
            {
                case 1:
                if (utn_getNombre(bufferNombre, 51, "Modifique Nombre\n", "No es un nombre valido\n", 2)==0)
                {
                    strncpy(pArray[id].name, bufferNombre, 51);
                    printf("Nombre modicado\n");
                    break;
                }
                case 2:
                if (utn_getNombre( bufferApellido, 51, "Modifique apellido del Empleado\n","No es un apellido valido\n", 3) == 0)
                {
                    strncpy(pArray[id].lastName, bufferApellido, 51);
                    printf("Apellido modicado\n");
                    break;
                }
                case 3:
                if (utn_getFloat(&bufferSalario,20, "Modifique Salario\n", "No es un precio valido\n",2 )== 0)
                {
                    pArray[id].salary =  bufferSalario;
                    printf("Salario modicado\n");
                    break;
                }
                case 4:
                if (utn_getEntero( &bufferSector , 20, "Modifique numero de Sector\n", "No es un sector valido\n", 3) == 0)
                {
                    pArray[id].sector =  bufferSector;
                    printf("Sector modicado\n");
                    break;
                }
                default :
                printf("Opcion no valida\n");
            }
            retorno = 0;
        }else
        {
            printf("No existe id\n");
        }
    }
return retorno;
}
/**
* \brief    evalua el id ingresado y en caso de exito y de haber informacion en ese id
*           borra la informacion
* \param pArray Recibe el array ingresado
* \param id es el numero a buscar
* \param limite Es el tamano maximo del string
*/
int utn_borrarEmpleado(empleadoDes* pArray, int len, int id)
{
	int retorno = -1;
    if(pArray != NULL && len > 0 && len>0 && id >= 0 )
	{
		if (pArray[id].isEmpty == 1)
		{
			 pArray[id].isEmpty = 0;
			 retorno = 0;
		}else
		{
			printf("No hay empleado con ese id\n");
		}
	}
  return retorno;
}
/**
* \brief    calcula el total y el promedio sobre el salario,
*           y muestra cuales empleados superan ese promedio.
* \param pArray Recibe el array ingresado
* \param limite Es el tamano maximo del string
*/
void getTotalPromedio(empleadoDes* pArray, int len)
{
	int i, j;
	float acumuladorSalario = 0;
	int contadorSuperan = 0;
    int contador = 0;
	if(pArray != NULL && len > 0 && len>0 )
	{
		for (i =0; i< len; i++ )
		{
			if(pArray[i].isEmpty == 1)
			{
				acumuladorSalario = acumuladorSalario + pArray[i].salary;
				contador++;
			}
		}
		if (acumuladorSalario > 0)
		{
			printf("el total es %f\n", acumuladorSalario);
			printf("El promedio es %f\n", acumuladorSalario/contador);
		}
		for (j =0; j< len; j++)
		{
			if (pArray[j].isEmpty == 1 && pArray[j].salary > (acumuladorSalario/contador))
			{
				printf("Id: %d\n", pArray[j].id);
				printf("Nombre: %s\n", pArray[j].name);
				printf("Apellido: %s\n ", pArray[j].lastName);
				printf("Salario: %f\n", pArray[j].salary);
				printf("Sector: %d\n", pArray[j].sector);
				printf("------------------------------------\n");
				contadorSuperan++;
				fflush(stdin);
			}
		}
		printf("la cantidad que superan el promedio %d\n", contadorSuperan);
	}
}
/**
* \brief    recibe una cadena y evalua si son datos validos,
*           en caso de exito agrega un empleado
* \param pArray Recibe el array ingresado
* \param limite Es el tamano maximo del string
*/
int addEmployees (empleadoDes* pArray,int limite)
{
	int retorno = -1;
	int i;
	char ingEmpleado;
	char bufferNombre[51];
	char bufferApellido[51];
	float bufferSalario;
	int bufferSector;
	if(pArray != NULL && limite > 0)
	{
		for (i = 0; i<limite; i++ )
		{
			if (pArray[i].isEmpty == 0 &&
				utn_getNombre( bufferNombre, limite, "Ingresar nombre de Empleado\n","No es un nombre valido", 3) == 0 &&
				utn_getNombre( bufferApellido, limite, "Ingresar apellido de Empleado\n","No es un apellido valido", 3) == 0 &&
				utn_getFloat( &bufferSalario, limite, "Ingrese Salario\n", "No es un salario valido", 3) == 0 &&
				utn_getEntero( &bufferSector , limite, "Ingresar numero de Sector\n", "No es un sector valido", 3) == 0)
			{
				pArray[i].id = i;
				strncpy(pArray[i].name, bufferNombre, 51);
				strncpy(pArray[i].lastName, bufferApellido, 51);
				pArray[i].salary =  bufferSalario;
				pArray[i].sector = bufferSector;
				pArray[i].isEmpty =  1;
				retorno = 0;
				printf("Desea ingresar otro empleado? Y/N\n");
				scanf("%c", &ingEmpleado);
				if (ingEmpleado == 'N')
				{
					break;
				}else if (ingEmpleado == 'Y')
				{
					continue;
				}else
				{
					printf("No es una opcion valida\n");
					break;
				}
			}
		}
	}
	return retorno;
}
/**
* \brief    recibe una cadena y ordena en primer caso por apellido
*           en caso de ser iguales por sector
* \param pArray Recibe el array ingresado
* \param limite Es el tamano maximo del string
* \param upOrDonw es el orden en cual se va mostar en caso de 1 es de mayor a menor si es 0 lo contrario
*/
int con_ordenarByNombre(empleadoDes* pBuffer,int limite,int upOrDonw)
{
  int i, j;
  int auxId;
  char auxNombre[50];
  char auxLastName[50];
  int auxSector;
  float auxSalario;
  if (pBuffer != NULL && limite > 0 && (upOrDonw == 0 || upOrDonw == 1))
    {
        for(i = 0; i < limite; i++)
        {
          j = i + 1;
                fflush(stdin);
                if(pBuffer[i].isEmpty == 1&& pBuffer[j].isEmpty == 1 && upOrDonw == 1 && strcmp(pBuffer[i].lastName,pBuffer[j].lastName) >0
                   || (strcmp(pBuffer[i].lastName,pBuffer[j].lastName) ==0 && pBuffer[i].sector > pBuffer[j].sector))
                {
                    auxId = pBuffer[j].id;
                    pBuffer[j].id = pBuffer[i].id;
                    pBuffer[i].id = auxId;

                    strncpy(auxLastName, pBuffer[j].lastName, 50);
                    strncpy(pBuffer[j].lastName,pBuffer[i].lastName, 50);
                    strncpy(pBuffer[i].lastName,auxLastName, 50);

                    strncpy(auxNombre, pBuffer[j].name, 50);
                    strncpy(pBuffer[j].name,pBuffer[i].name, 50);
                    strncpy(pBuffer[i].name,auxNombre, 50);

                    auxSalario = pBuffer[j].salary;
                    pBuffer[j].salary = pBuffer[i].salary;
                    pBuffer[i].salary = auxSalario;

                    auxSector = pBuffer[j].sector;
                    pBuffer[j].sector = pBuffer[i].sector;
                    pBuffer[i].sector = auxSector;
                }else if(pBuffer[i].isEmpty == 1&& pBuffer[j].isEmpty == 1 && upOrDonw == 0 && strcmp(pBuffer[i].lastName,pBuffer[j].lastName) <0
                         || strcmp(pBuffer[i].lastName,pBuffer[j].lastName) ==0 && pBuffer[i].sector < pBuffer[j].sector)
                {
                    auxId = pBuffer[j].id;
                    pBuffer[j].id = pBuffer[i].id;
                    pBuffer[i].id = auxId;

                    strncpy(auxLastName, pBuffer[j].lastName, 50);
                    strncpy(pBuffer[i+1].lastName,pBuffer[i].lastName, 50);
                    strncpy(pBuffer[i].lastName,auxLastName, 50);

                    strncpy(auxNombre, pBuffer[j].name, 50);
                    strncpy(pBuffer[i+1].name,pBuffer[i].name, 50);
                    strncpy(pBuffer[i].name,auxNombre, 50);

                    auxSalario = pBuffer[j].salary;
                    pBuffer[j].salary = pBuffer[i].salary;
                    pBuffer[i].salary = auxSalario;

                    auxSector = pBuffer[j].sector;
                    pBuffer[j].sector = pBuffer[i].sector;
                    pBuffer[i].sector = auxSector;
                }
        }
    }
    return 1;
}
/**
* \brief    muestra el menu principal del programa
* \param pArray Recibe el array ingresado
* \param limite Es el tamano maximo del string
*/
int mostrarMenu (empleadoDes* pArray, int limite)
{
	int retorno = -1;
	char resp;
	int resp2,i, flag =0;
	int bufferID;
	if (pArray != NULL && limite>0)
	{
		do
		{
			printf("a - Carga de empleado\n");
			printf("b - Modificar de empleado por id\n");
			printf("c - Baja de empleado por id\n");
			printf("d - Informar\n");
			printf("e - Salir\n");
            fflush(stdin);
			 //__fpurge(stdin);
			scanf("%c",&resp);
			switch(resp)
			{
				case 'a':
				if (addEmployees (pArray, limite) == 0)
				{
				 printf("Empleado cargado\n")	;
				 break;
				}
				break;
				case 'b':
				// modificar
				for (i = 0; i< limite ; i++)
                {
                  if (pArray[i].isEmpty == 1)
                  {
                    flag = 1;
                    break;
                   }
                }
                  if (flag == 0)
                  {
                      printf("No hay informacion cargada\n");
                  }
				if ( flag == 1 && utn_getEntero(&bufferID, limite, "Ingrese id\n","No es un id valido \n", 3) == 0 &&
                     utn_getEmpleadoModificar( pArray, limite, bufferID) == 0)
				{
					printf("Empleado Modificado\n");
					flag = 0;
					break;
				}
				break;
				case 'c':
				for (i = 0; i< limite ; i++)
                {
                  if (pArray[i].isEmpty == 1)
                  {
                    flag = 1;
                    break;
                   }
                }
                  if (flag == 0)
                  {
                      printf("No hay informacion cargada\n");
                  }
                    if ( flag == 1 && utn_getEntero(&bufferID, limite, "Ingrese id\n","No es un id valido \n", 3) == 0 &&
                         utn_borrarEmpleado(pArray, limite, bufferID) == 0)
                    {
                        printf("Empleado Borrado\n");
                            flag = 0;
                        break;
                    }
                    break;
				case 'd':
				//informar
				for (i = 0; i< limite ; i++)
                {
                  if (pArray[i].isEmpty == 1)
                  {
                    flag = 1;
                    break;
                   }
                 }
                  if (flag == 0)
                  {
                      printf("No hay informacion cargada\n");
                  }

                if (flag == 1)
                {
                    printf("1- Lista de empleados\n");
                    printf("2- Total y promedio de salarios y cuantos empleados superan el salario promerio\n");
                    scanf("%d",&resp2);
                    switch(resp2)
                    {
                        case 1:
                        con_ordenarByNombre(pArray, limite, 1);
                        printProducto(pArray, limite);
                        break;
                        case 2:
                        getTotalPromedio(pArray, limite);
                        break;
                        default:
                        printf("Opcion no valida");
                        break;
                     }
                }
                flag = 0;
                break;
				case 'e':
				printf("Salio");
				retorno = 0;
				break;
				default:
				printf("No es una opcion correcta\n");
				break;
			}
		}while(resp != 'e');
	}
	return retorno;
}
