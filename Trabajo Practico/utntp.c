#include <stdio.h>
#include <stdlib.h>
#include "utntp.h"
/*
*\brief Funcion que suma 2 numeros y te devuelve el resultado de la suma.
*\param numero1 Es el primer numero ingresado por el usuario
*\param numero2 Es el segundo numero ingresado por el usuario
*/
float getSuma (float numero1, float numero2)
{
	float total;
	total = numero1 + numero2;
	return total;
}
/*
*\brief Funcion que resta 2 numeros y te devuelve el resultado de la resta.
*\param numero1 Es el primer numero ingresado por el usuario
*\param numero2 Es el segundo numero ingresado por el usuario
*\param pResultado Es la variable para devolver el resultado de la suma
*/
float getResta (float numero1, float numero2)
{
	float total;
	total = numero1 - numero2;
	return total;
}
/*
*\brief Funcion que multiplicar 2 numeros y te devuelve el resultado de la multiplicacion.
*\param numero1 Es el primer numero ingresado por el usuario
*\param numero2 Es el segundo numero ingresado por el usuario
*/
float getMultiplicar (float numero1, float numero2)
{
	float total;
	total = numero1 * numero2;
	return total;
}
/*
*\brief Funcion que divide 2 numero y te devuelve el resultado de la division.
*\param numero1 Es el primer numero ingresado por el usuario
*\param divisor Es el segundo numero ingresado por el usuario
*/
float getDividir (float numero1, float numero2)
{
	float total;
	total = numero1 / numero2;
	return total;
}
/*
*\brief Funcion  que saca el factorial de un numero
*\param numero Es el numero ingresado por el usuario
*/
int getFactorial(int numero)
{
	int res;
	if (numero == 1)
		return 1;
	    res = numero* getFactorial(numero-1);
	    return res;
}
