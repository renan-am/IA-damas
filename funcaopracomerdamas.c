#include <stdio.h>
#include <stdlib.h>
#include "func_declarations.h"

#define possibilitiesSize 4


static PATH *auxWaysToWinDama; // vetor auxiliar com o caminho atual.
static PATH **waysToWinDama;//matriz que vai guardar os caminhos possiveis.

static int *tamanhoDama;

static int possiblePathsXDama[possibilitiesSize] = {1, -1, -1, 1};//deve ser global
static int possiblePathsYDama[possibilitiesSize] = {-1, -1, 1, 1};//deve ser global
static int waySizeDama = 0, counterWaysDama = 0;// deve estar na main e ser zerada antes de chamar PossiblePaths(toda vez que for chamar tem que zerar)



static void saveWayDama(PATH *auxWay, int auxSize, PATH **bankOfWays, int counterWaysDama){

	for(int i = 0; i < auxSize; i++){
		bankOfWays[counterWaysDama][i] = auxWaysToWinDama[i];
		tamanhoDama[counterWaysDama] = auxSize; 
	}
	
}

static int PossiblePathsDama(BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i){

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
			
			if(checarSeCome(vet ,posAtualX, posAtualY, posAtualX+possiblePathsXDama[i], posAtualY+possiblePathsYDama[i], type) && temp == 3){
					//printf ("ali\n");

					auxWaysToWinDama[waySizeDama].posXfinal = posAtualX + 2*possiblePathsXDama[i];
					auxWaysToWinDama[waySizeDama].posYfinal = posAtualY + 2*possiblePathsYDama[i];
					auxWaysToWinDama[waySizeDama].posXcomida = posAtualX+possiblePathsXDama[i];
					auxWaysToWinDama[waySizeDama].posYcomida = posAtualY+possiblePathsYDama[i];
					waySizeDama++;

					//muda o tipo da pedra comida pra evitar ignorar as pedras comidas
					aux = vet[(posAtualY + possiblePathsYDama[i]) * COL_MAX + posAtualX+possiblePathsXDama[i]].tipo;
					vet[(posAtualY+possiblePathsYDama[i]) * COL_MAX + posAtualX+possiblePathsXDama[i]].tipo = type;
					flag2 = PossiblePathsDama(vet, posAtualX + 2*possiblePathsXDama[i], posAtualY + 2*possiblePathsYDama[i], type, (i+2)%4);
					vet[(posAtualY+possiblePathsYDama[i]) * COL_MAX + posAtualX+possiblePathsXDama[i]].tipo = aux;
					waySizeDama--;


			}else if (temp == 4){
				//printf ("sfyysaguidasghdhasudhaush\n");
				do{
					if(checarSeCome(vet ,posAtualX+z*possiblePathsXDama[i], posAtualY+z*possiblePathsYDama[i], posAtualX+((z+1)*possiblePathsXDama[i]), posAtualY+((z+1)*possiblePathsYDama[i]), type) && temp != 3){
				
						auxWaysToWinDama[waySizeDama].posXfinal = posAtualX + (z+2)*possiblePathsXDama[i];
						auxWaysToWinDama[waySizeDama].posYfinal = posAtualY + (z+2)*possiblePathsYDama[i];
						auxWaysToWinDama[waySizeDama].posXcomida = posAtualX+((z+1)*possiblePathsXDama[i]);
						auxWaysToWinDama[waySizeDama].posYcomida = posAtualY+((z+1)*possiblePathsYDama[i]);
					
						waySizeDama++;
						aux = vet[(posAtualY+((z+1)*possiblePathsYDama[i])) * COL_MAX + posAtualX+((z+1)*possiblePathsXDama[i])].tipo;
						vet[(posAtualY+possiblePathsYDama[i]) * COL_MAX + posAtualX+possiblePathsXDama[i]].tipo = type;
						PossiblePathsDama(vet, posAtualX + (z+2)*possiblePathsXDama[i], posAtualY + (z+2)*possiblePathsYDama[i], type, (i+2)%4);
						vet[(posAtualY+((z+1)*possiblePathsYDama[i])) * COL_MAX + posAtualX+((z+1)*possiblePathsXDama[i])].tipo = aux;
						waySizeDama--;
					}
					z++;


				}while(validar(vet, posAtualX+z*possiblePathsXDama[i], posAtualY+z*possiblePathsYDama[i]) == 0);
			}

				if(j == temp-1 && validar(vet, posAtualX+possiblePathsXDama[i2], posAtualY+possiblePathsYDama[i2]) == 0 && temp == 3){
					//printf ("here\n");					
					j = -1;
					posAtualX += possiblePathsXDama[i2];
					posAtualY += possiblePathsYDama[i2];
					i = i3;

			}

		}

		
		saveWayDama(auxWaysToWinDama, waySizeDama, waysToWinDama, counterWaysDama);
		counterWaysDama++;
		
		return 1;
			
}

PATH **EncontrarCaminhoDama (BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i){
		auxWaysToWinDama = calloc(100, sizeof(PATH));
		waysToWinDama = calloc(100,sizeof(PATH*));
		tamanhoDama = calloc (100, sizeof(int));

		for(int i = 0; i < 100; i++)
			waysToWinDama[i] = calloc(100,sizeof(PATH));

		PossiblePathsDama (tabuleiro, posAtualX, posAtualY, type, i);

		int maximo = 0;
     	int *indMAX =NULL;


		for (int i = 0; i <100; i++){
			if (maximo < tamanhoDama[i]){
				maximo = tamanhoDama[i];
			}
		}

		indMAX = calloc (100, sizeof(int));

		int k = 0;
		for (int i = 0; i<100; i++)
			if (tamanhoDama[i] == maximo){
				indMAX[k] = i;
				k++; 
			}

		PATH **best;
		best = calloc (100, sizeof(PATH*));



		for (i = 0; i<100; i++)
			best[i] = calloc (50, sizeof(PATH));

		for (i = 0; i< k; i++)
			for (int j = 0; j<maximo+1; j++){
				best[i][j].posXfinal = waysToWinDama[indMAX[i]][j].posXfinal;
				best[i][j].posYfinal = waysToWinDama[indMAX[i]][j].posYfinal;
				best[i][j].posXcomida = waysToWinDama[indMAX[i]][j].posXcomida;
				best[i][j].posYcomida = waysToWinDama[indMAX[i]][j].posYcomida;
			}


		free (waysToWinDama);
		free (auxWaysToWinDama);
		free (indMAX);
		free (tamanhoDama);

		waySizeDama = 0;
		counterWaysDama = 0;

		return best;


}


	
