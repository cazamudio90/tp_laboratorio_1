#ifndef UTN_H_INCLUDED
#define UTN_H_INCLUDED
typedef struct eEmplados
{
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int isEmpty;
}empleadoDes;
int initEmployees(empleadoDes* pArray, int limite);
int utn_getEntero(  int *pEntero, int limite, char *mensaje,char *mensajeError, int reintentos);
int utn_getFloat(   float *pFloat, int limite, char *mensaje,char *mensajeError, int reintentos);
int utn_getNombre(  char* pNombre,int limite, char* msg, char* msgErr, int reintentos);
int initEmployees(empleadoDes* pArray, int limite);
void getTotalPromedio(empleadoDes* pArray, int len);
void printProducto(empleadoDes* pArray, int len);
int utn_borrarEmpleado(empleadoDes* pArray, int len, int id);
int utn_getEmpleadoModificar(empleadoDes* pArray, int len, int id);
int mostrarMenu (empleadoDes* pArray, int limite);
int addEmployees (empleadoDes* pArray,int limite);
int con_ordenarByNombre(empleadoDes* pBuffer,int limite,int upOrDonw);
#endif // UTN_H_INCLUDED
