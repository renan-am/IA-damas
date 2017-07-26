#include <stdio.h>
#include <stdlib.h>
#include "func_declarations.h"

#define possibilitiesSize 4


static PATH *auxWaysToWin; // vetor auxiliar com o caminho atual.
PATH **waysToWin;//matriz que vai guardar os caminhos possiveis.

static tamanho[100];

static int possiblePathsX[possibilitiesSize] = {1, -1, -1, 1};//deve ser global
static int possiblePathsY[possibilitiesSize] = {-1, -1, 1, 1};//deve ser global
static int waySize = 0, counterWays = 0;// deve estar na main e ser zerada antes de chamar PossiblePaths(toda vez que for chamar tem que zerar)



void saveWay(PATH *auxWay, int auxSize, PATH **bankOfWays, int counterWays){

	for(int i = 0; i < auxSize; i++){
		bankOfWays[counterWays][i] = auxWaysToWin[i];
		tamanho[counterWays] = auxSize; 
	}
	
}

int PossiblePaths(BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i){

	int temp = 0;

	if (i == -1)
		temp = 4;
	else
		temp = 3;


	i = (i+1)%4;
	int flag2 = 0;

	BOARD vet[COL_MAX*LIN_MAX];
	int aux;
	for (int linha = 0; linha < LIN_MAX; linha++)
				for (int coluna = 0; coluna < COL_MAX; coluna++)
					 vet[POS].tipo = tabuleiro[POS].tipo;


		for(int j = 0; j < temp; j++, i = (i+1)%4 ){
			if(checarSeCome(vet ,posAtualX, posAtualY, posAtualX+possiblePathsX[i], posAtualY+possiblePathsY[i], type)){
				auxWaysToWin[waySize].posXfinal = posAtualX + 2*possiblePathsX[i];
				auxWaysToWin[waySize].posYfinal = posAtualY + 2*possiblePathsY[i];
				auxWaysToWin[waySize].posXcomida = posAtualX+possiblePathsX[i];
				auxWaysToWin[waySize].posYcomida = posAtualY+possiblePathsY[i];
				waySize++;

				aux = vet[(posAtualY + possiblePathsY[i]) * COL_MAX + posAtualX+possiblePathsX[i]].tipo;
				vet[(posAtualY+possiblePathsY[i]) * COL_MAX + posAtualX+possiblePathsX[i]].tipo = type;
				flag2 = PossiblePaths(vet, posAtualX + 2*possiblePathsX[i], posAtualY + 2*possiblePathsY[i], type, (i+2)%4);
				vet[(posAtualY+possiblePathsY[i]) * COL_MAX + posAtualX+possiblePathsX[i]].tipo = aux;
				waySize--;
			}
		}

		if (!flag2){
		saveWay(auxWaysToWin, waySize, waysToWin, counterWays);
		counterWays++;
		
		return 1;
		}
		else
		return 0;	
}

PATH **EncontrarCaminho (BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i){
		auxWaysToWin = calloc(100, sizeof(PATH));
		waysToWin = calloc(100,sizeof(PATH*));

		for(int i = 0; i < 100; i++)
			waysToWin[i] = calloc(100,sizeof(PATH));

		PossiblePaths (tabuleiro, posAtualX, posAtualY, type, i);

		int maximo = 0;
		int *indMAX;


		for (int i = 0; i <100; i++){
			if (maximo < tamanho[i]){
				maximo = tamanho[i];
			}
		}

		for (int i = 0, int k =0; i<100; i++)
			if (tamanho[i] == maximo)
				indMAX[k++] = i; 

		PATH **best;
		best = calloc (k-1, sizeof(PATH*));

		for (i = 0; i<k; i++)
			best[i] = calloc (maximo+1, sizeof(PATH));

		for (i = 0; i< k; i++)
			for (int j = 0; j<maximo+1; j++){
				best[i][j].posXfinal = waysToWin[indMAX[i]][j].posXfinal;
				best[i][j].posYfinal = waysToWin[indMAX[i]][j].posYfinal;
				best[i][j].posXcomida = waysToWin[indMAX[i]][j].posXcomida;
				best[i][j].posYcomida = waysToWin[indMAX[i]][j].posYcomida;
			}

		free (waysToWin);
		free (auxWaysToWin);
		free (indMAX);

		waySize = 0;
		counterWays = 0;

		return **best;


}


	
