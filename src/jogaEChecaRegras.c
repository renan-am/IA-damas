#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "module.h"
#include "func_declarations.h"





void jogaEChecaRegras(char acao, int* coluna, int* linha){
	
	while(1){
		printf ("Digite a coluna da pedra a ser movida: ");
		scanf ("%d", &coluna);
		coluna--;
		if (coluna >= COL_MAX || coluna < 0)
		printf ("Coluna invalida, tente novamente\n");
		else
		break;
	}


	while(1){
		printf ("Digite a linha da pedra a ser movida: ");
		scanf ("%d", &linha);
		linha--;
		if (linha >= COL_MAX || linha < 0)
			printf ("Linha invalida, tente novamente\n");
		else
			break;
	}


	





}





