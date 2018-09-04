#include <stdio.h>
#include <stdlib.h>
#include "utntp.h"
int main()
{
	// Variables
	  float numero1;
	  float numero2;
	  float suma;
      float resta;
      float division;
      float multiplicar;
	  int factorialA;
	  int factorialB;
	  int opcion;
	  int flag;
	  int flag1;
	  int flag2;
	  char letra;
    do
	{
		printf("ingrese una opcion (1 al 5)\n");
		printf("1- Ingresar 1er operando (A = x)\n");
		printf("2- Ingresar 2do operandon (B = Y)\n");
		printf("3- Calcular todas las operaciones\n");
		printf("4- Informar resultados\n");
		printf("5- salir\n");
		if (scanf("%d",&opcion)== 1)
        {
		switch(opcion)
		{
			case 1:
			printf("1- Ingresar 1er operando (A = x)\n");
			while (scanf("%f", &numero1) == 0)
			{
			    if (scanf("%s", &numero1) == 1)
                {
                    printf("Error. Reingrese numero\n");
                }
            }
			flag1 = 1;
			printf("A = %f\n", numero1);
			break;
			case 2:
			printf("2- Ingresar 2do operando(B = Y)\n");
			while (scanf("%f", &numero2) == 0)
			{
				if (scanf("%s", &numero2) == 1)
                {
                 printf("Error. Reingrese numero\n");
                }
			}
			printf("B = %f\n", numero2);
			flag2 = 1;
			break;
			case 3:
			if (flag1 == 1 && flag2 == 1)
			{
                suma = getSuma(numero1,numero2);
				resta = getResta(numero1, numero2);
				if (numero2 != 0)
                {
                 division = getDividir(numero1, numero2);
                }else
                {
                    printf("No se puede dividir por 0 !!\n");
                    break;
                }
				multiplicar = getMultiplicar(numero1, numero2);
				factorialA = getFactorial(numero1);
				factorialB = getFactorial(numero2);
				printf("Se calcularon todas las operaciones\n");
				break;
			} else
			{
				printf("Debe ingresar los 2 operando para poder calcular\n");
				break;
			}
			case 4:
			if (flag1 == 1 && flag2 == 1)
			{
				printf("El resultado de A+B es: %f\n", suma);
				printf("El resultado de A-B es: %f\n", resta);
				if (numero2 != 0)
				{
					printf("El resultado de A/B es: %f\n", division);
				} else
				{
					printf("No se puede divir por 0 !!\n");
				}
				 printf("El resultado de A*B es: %f\n", multiplicar);
				 if (numero1 > 1 && numero2 > 1)
				 {
					printf("El factorial de A es: %d y el factorial de B es: %d\n", factorialA, factorialB);
				 } else
				 {
					printf("No se puede calcular factorial\n");
				 }
			}else
			{
				printf("Debe ingresar los 2 operando para poder calcular e informar los resultados\n");
			}
			 break;
			 case 5:
			 printf("Salio");
			 return 0;
			 default:
			 printf("Opcion no valida\n");
		}
        }else if (scanf("%s", &opcion)==1)
        {
            printf("Error ingrese una opcion correcta");
        }
		flag = 1;
	} while (opcion != 5 || flag == 1);
  return 0;
}
