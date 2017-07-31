#include <stdio.h>
#include <stdlib.h>
#include "func_declarations.h"

#define possibilitiesSize 4


static PATH *auxWaysToWin; // vetor auxiliar com o caminho atual.
PATH **waysToWin;//matriz que vai guardar os caminhos possiveis.

static int *tamanho;

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
	int i2 = i;
	int i3 = i;
	if (i == -1)
		temp = 4;
	else
		temp = 3;

	//printf ("temp = %d\n", temp);
	i = (i+1)%4;
	i2 = (i+1)%4;
	int flag2 = 0;

	BOARD vet[COL_MAX*LIN_MAX];
	int aux;
	for (int linha = 0; linha < LIN_MAX; linha++)
				for (int coluna = 0; coluna < COL_MAX; coluna++)
					 vet[POS].tipo = tabuleiro[POS].tipo;


		for(int j = 0; j < temp; j++, i = (i+1)%4 ){

			int z = 0;
			
			if(checarSeCome(vet ,posAtualX, posAtualY, posAtualX+possiblePathsX[i], posAtualY+possiblePathsY[i], type) && temp == 3){
					//printf ("ali\n");

					auxWaysToWin[waySize].posXfinal = posAtualX + 2*possiblePathsX[i];
					auxWaysToWin[waySize].posYfinal = posAtualY + 2*possiblePathsY[i];
					auxWaysToWin[waySize].posXcomida = posAtualX+possiblePathsX[i];
					auxWaysToWin[waySize].posYcomida = posAtualY+possiblePathsY[i];
					waySize++;

					//muda o tipo da pedra comida pra evitar ignorar as pedras comidas
					aux = vet[(posAtualY + possiblePathsY[i]) * COL_MAX + posAtualX+possiblePathsX[i]].tipo;
					vet[(posAtualY+possiblePathsY[i]) * COL_MAX + posAtualX+possiblePathsX[i]].tipo = type;
					flag2 = PossiblePaths(vet, posAtualX + 2*possiblePathsX[i], posAtualY + 2*possiblePathsY[i], type, (i+2)%4);
					vet[(posAtualY+possiblePathsY[i]) * COL_MAX + posAtualX+possiblePathsX[i]].tipo = aux;
					waySize--;


			}else if (temp == 4){
				//printf ("sfyysaguidasghdhasudhaush\n");
				do{
					if(checarSeCome(vet ,posAtualX+z*possiblePathsX[i], posAtualY+z*possiblePathsY[i], posAtualX+((z+1)*possiblePathsX[i]), posAtualY+((z+1)*possiblePathsY[i]), type) && temp != 3){
				
						auxWaysToWin[waySize].posXfinal = posAtualX + (z+2)*possiblePathsX[i];
						auxWaysToWin[waySize].posYfinal = posAtualY + (z+2)*possiblePathsY[i];
						auxWaysToWin[waySize].posXcomida = posAtualX+((z+1)*possiblePathsX[i]);
						auxWaysToWin[waySize].posYcomida = posAtualY+((z+1)*possiblePathsY[i]);
					
						waySize++;
						aux = vet[(posAtualY+((z+1)*possiblePathsY[i])) * COL_MAX + posAtualX+((z+1)*possiblePathsX[i])].tipo;
						vet[(posAtualY+possiblePathsY[i]) * COL_MAX + posAtualX+possiblePathsX[i]].tipo = type;
						PossiblePaths(vet, posAtualX + (z+2)*possiblePathsX[i], posAtualY + (z+2)*possiblePathsY[i], type, (i+2)%4);
						vet[(posAtualY+((z+1)*possiblePathsY[i])) * COL_MAX + posAtualX+((z+1)*possiblePathsX[i])].tipo = aux;
						waySize--;
					}
					z++;


				}while(validar(vet, posAtualX+z*possiblePathsX[i], posAtualY+z*possiblePathsY[i]) == 0);
			}

				if(j == temp-1 && validar(vet, posAtualX+possiblePathsX[i2], posAtualY+possiblePathsY[i2]) == 0 && temp == 3){
					//printf ("here\n");					
					j = -1;
					posAtualX += possiblePathsX[i2];
					posAtualY += possiblePathsY[i2];
					i = i3;

			}

		}

		
		saveWay(auxWaysToWin, waySize, waysToWin, counterWays);
		counterWays++;
		
		return 1;
			
}

PATH **EncontrarCaminho (BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i){
		auxWaysToWin = calloc(100, sizeof(PATH));
		waysToWin = calloc(100,sizeof(PATH*));
		tamanho = calloc (100, sizeof(int));

		for(int i = 0; i < 100; i++)
			waysToWin[i] = calloc(100,sizeof(PATH));

		PossiblePaths (tabuleiro, posAtualX, posAtualY, type, i);

		int maximo = 0;
     	int *indMAX =NULL;


		for (int i = 0; i <100; i++){
			if (maximo < tamanho[i]){
				maximo = tamanho[i];
			}
		}

		indMAX = calloc (100, sizeof(int));

		int k = 0;
		for (int i = 0; i<100; i++)
			if (tamanho[i] == maximo){
				indMAX[k] = i;
				k++; 
			}

		PATH **best;
		best = calloc (100, sizeof(PATH*));



		for (i = 0; i<100; i++)
			best[i] = calloc (50, sizeof(PATH));

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
		free (tamanho);

		waySize = 0;
		counterWays = 0;

		return best;


}


	
