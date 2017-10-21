#include <stdio.h>
#include <stdlib.h>
#include "func_declarations.h"

BOARD *GAME (int c_origem, int l_origem, int c_destino, int l_destino, PATH *pedrascomidas, int hide){
	static int jogoiniciou = 0;     //inicializa tabuleiro somente uma vez
	static BOARD *tabuleiro;


	if (!jogoiniciou){
		tabuleiro = calloc (COL_MAX*LIN_MAX, sizeof(BOARD));
		posicionarpedras(tabuleiro);

		/*
	int vet[COL_MAX*LIN_MAX] = {0, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 2, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 1, 0, 0, 0,
								0, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 1, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 0, 0, 0, 0,
								};

				for (int linha = 0; linha < LIN_MAX; linha++)
					for (int coluna = 0; coluna < COL_MAX; coluna++){
						tabuleiro[POS].tipo = vet[POS];
						if (vet[POS] == 2)
						tabuleiro[POS].classe = 1;
						else
						tabuleiro[POS].classe = vet[POS];
					}
	*/





		jogoiniciou = 1;
		if (!hide){
			system ("tput reset");
			imprimir(tabuleiro);
		}
	}


	if (c_origem == l_origem && l_origem == c_destino && c_destino == l_destino && c_origem == 0){
		return tabuleiro;
	}

	if (validar (tabuleiro, c_origem, l_origem) < 1  || validar (tabuleiro, c_destino, l_destino) != 0){
		//printf ("*game recebeu valorimpróprio\nc_origem = %d    l_origem = %d\nc_destino = %d    l_destino = %d\n", c_origem, l_origem, c_destino, l_destino);
		return NULL;
	}

	mover (tabuleiro, c_origem, l_origem, c_destino, l_destino);
	turno = (turno%2)+1;


	if (pedrascomidas){
		remover (tabuleiro, pedrascomidas);
	}

	for (int coluna = 0; coluna < COL_MAX; coluna++){
		int linha = 0;
		if (tabuleiro[POS].tipo == 2 && tabuleiro[POS].classe == 1)
			tabuleiro[POS].classe = 2;
		linha = 7;
		if (tabuleiro[POS].tipo == 1 && tabuleiro[POS].classe == 1)
			tabuleiro[POS].classe = 2;
	}
	if (!hide){
		system ("tput reset");
		imprimir(tabuleiro);
	}
	return tabuleiro;
}

void posicionarpedras (BOARD *tab){   //inicializa o tabuleiro, com pedras tipo 1 na parte superior e tipo 2 na parte inferior
	int linha, coluna;

	for (linha = 0; linha < LIN_MAX; linha++)
		for (coluna = 0; coluna < COL_MAX; coluna++){
			tab[POS].tipo = 0;
			tab[POS].classe = 0;
		}

	for (linha = 0; linha < (LIN_MAX-2)/2; linha++)
		for (coluna = (linha+1)%2; coluna < COL_MAX; coluna += 2){	// (linha+1) % 2 garante que as casas serão alternadas, ex: 1ª linha as casas pretas começam na 2ª coluna, 2ª linha começam na 1ª coluna, etc.
			tab[POS].tipo = 1;
			tab[POS].classe = 1;
		}

	for (linha = LIN_MAX - (LIN_MAX-2)/2; linha < LIN_MAX; linha++)
		for (coluna = (linha+1)%2; coluna < COL_MAX; coluna += 2){	// (linha+1) % 2 garante que as casas serão alternadas, ex: 1ª linha as casas pretas começam na 2ª coluna, 2ª linha começam na 1ª coluna, etc.
			tab[POS].tipo = 2;
			tab[POS].classe = 1;

		}
	for (linha = 0; linha < LIN_MAX; linha++)
		for (coluna = linha%2; coluna < COL_MAX; coluna += 2){
			tab[POS].tipo = -1;
			tab[POS].classe = -1;
		}
}

void mover (BOARD *tab, int c_origem, int l_origem, int c_destino, int l_destino){    //move pedra da posicao de origem para a posiçao destino no tabuleiro *tab
	int aux;
	aux = tab[l_origem*COL_MAX+c_origem].tipo;
	tab[l_origem*COL_MAX+c_origem].tipo = tab[l_destino*COL_MAX+c_destino].tipo;
	tab[l_destino*COL_MAX+c_destino].tipo = aux;

	aux = tab[l_origem*COL_MAX+c_origem].classe;
	tab[l_origem*COL_MAX+c_origem].classe = tab[l_destino*COL_MAX+c_destino].classe;
	tab[l_destino*COL_MAX+c_destino].classe = aux;
}

int validar (BOARD *tab, int coluna, int linha){ // retorna < 0 para posições impossíveis, ou retorna tipo
	if (coluna < 0 || coluna >= COL_MAX || linha < 0 || linha >= LIN_MAX)
		return -2;
	else
		return tab[POS].tipo;
}

int checarSeCome (BOARD *tab, int c_origem, int l_origem, int c_alvo, int l_alvo, int tipo){    // retorna 0 se a pedra nao puder ser comida, retorna 1 se puder. se int tipo = 0, sera usado o tipo da posicao de origem
	if (tipo == 0)
		tipo = tab[l_origem*COL_MAX+c_origem].tipo;

	int c_final = 0, l_final = 0;
	c_final = 2 * c_alvo - c_origem;
	l_final = 2 * l_alvo - l_origem;

	if (c_final < 0 || l_final < 0)
		return 0;
	else if (tab[l_alvo*COL_MAX+c_alvo].tipo <= 0)
		return 0;
	else if (tipo == tab[l_alvo*COL_MAX+c_alvo].tipo)
		return 0;
	else if (c_final < 0 || l_final < 0 || c_final >= COL_MAX || l_final >= LIN_MAX)
		return 0;
	else if (tab[l_final*COL_MAX+c_final].tipo != 0)
		return 0;
	else
		return 1;
}


void remover (BOARD *tab, PATH *pedrascomidas){
	int i = 0;
	while (pedrascomidas[i].posXcomida != 0 && pedrascomidas[i].posYcomida != 0){
		tab[pedrascomidas[i].posYcomida * COL_MAX + pedrascomidas[i].posXcomida].tipo = 0;
		tab[pedrascomidas[i].posYcomida * COL_MAX + pedrascomidas[i].posXcomida].classe = 0;
		i++;
	}
}


void imprimir (BOARD *tab){ // imprime tabuleiro e legenda das linhas e colunas
	int linha, coluna;

	for (linha = 0; linha < LIN_MAX+2; linha++){

		if (linha == LIN_MAX){  // pula uma linha para separar a legenda das colunas
				printf("\n");
				continue;
		}


		for (coluna = 0; coluna < COL_MAX; coluna++){
			if (linha == LIN_MAX+1){           // imprime legenda da coluna e ignora o resto do loop
				printf (" %c ", (64)+(coluna+1));
				continue;
			}


			if (tab[POS].tipo > 0 && tab[POS].classe == 1){     //imprime as pedras e substitui 0 por espaços em branco
				printf (" %.1d ", tab[POS].tipo);
			} else if (tab[POS].tipo > 0 && tab[POS].classe == 2) {
				printf (" %d*", tab[POS].tipo);
			} else {
				printf("   ");
			}
		}
		if (linha == LIN_MAX+1)
			printf ("\n");
		else
			printf("  %d\n", linha+1);

	}
}


int checarAcao (BOARD *tab, int coluna, int linha, PIECES **usefulPieces, DYNAMICVEC *usefulPiecesParameters){ //retorna 0 se não houver nenhuma ação possivel, retorna 1 se puder se movimentar, retorna 2 se puder capturar

	int flagcomeu = 0;
	int flagmoveu = 0;

		for (int i = -1; i < 2; i += 2){
			for (int j = -1; j < 2; j += 2){
				if (tab[POS].classe == 1){
					if (checarSeCome(tab, coluna, linha, coluna+i, linha+j, 0) == 1){ //checar se pode capturar alguma coisa
						flagcomeu = 1;
						usefulPiecesFunction(linha, coluna, usefulPieces, usefulPiecesParameters);
						return 2;
					}
					else if (validar (tab, coluna+i, linha+j) == 0 && tab[POS].tipo > 0)
						flagmoveu = 1;
				}	else if (tab[POS].classe == 2){
						for (int k = 0; validar(tab, coluna+((k+1)*i), linha+((k+1)*j)) >= 0; k++){
							if (checarSeCome(tab, coluna+k*i, linha+k*j,  coluna+((k+1)*i), linha+((k+1)*j), tab[POS].tipo)){
								flagcomeu = 1;
								usefulPiecesFunction(linha, coluna, usefulPieces, usefulPiecesParameters);
								return 2;
							}
							else if (validar (tab, coluna+i, linha+j) == 0 && tab[POS].tipo > 0)
								flagmoveu = 1;
						}
				}
			}
		}

	if (flagcomeu)
		return 2;
	else if (flagmoveu)
		return 1;
	else
		return 0;
}

char checarJogada (BOARD *tab, int jogador, PIECES **usefulPieces, DYNAMICVEC *usefulPiecesParameters){
	int jogada = 0, aux = 0;
	int flagmoveu = 0, flagcomeu = 0;

	for (int linha = 0; linha < LIN_MAX; linha++){
		for (int coluna = 0; coluna < COL_MAX; coluna++){
			if (tab[POS].tipo == jogador){
				aux = checarAcao (tab, coluna, linha, usefulPieces, usefulPiecesParameters);
				if (aux == 2)
					flagcomeu = 1;
				else if (aux == 1)
					flagmoveu = 1;
			}
		}
	}

	if (flagcomeu)
		return 'c';
	if (flagmoveu)
		return 'm';
	else
		return 'x';

}

void usefulPiecesFunction (int line, int column, PIECES **usefulPieces, DYNAMICVEC *usefulPiecesParameters){
	PIECES *aux = NULL;

	if(*usefulPieces == NULL){
		usefulPiecesParameters->capacity = 2;
		usefulPiecesParameters->size = 1;
		*usefulPieces = malloc(2*sizeof(PIECES));

	}else{
		(usefulPiecesParameters->size)++;
		if(usefulPiecesParameters->size == usefulPiecesParameters->capacity){
			(usefulPiecesParameters->capacity) *= 2;
			aux = realloc(*usefulPieces, (usefulPiecesParameters->capacity) * sizeof(PIECES));
			if (!aux){
				printf ("Erro de realloc na func usefulpieces\n");
			}
			*usefulPieces = aux;

		}

	}

		(*usefulPieces)[(usefulPiecesParameters->size) -1].line = line;
		(*usefulPieces)[(usefulPiecesParameters->size) -1].column = column;

}

DYNAMICVEC *goodPaths(BOARD *tab, int Xposition, int Yposition, int classe , int tipo){

	int pathX[4] = { 1, -1, -1, 1};
	int pathY[4] = {-1, -1, 1, 1};

	if(classe == 1){

		DYNAMICVEC *pathResult = malloc(sizeof(DYNAMICVEC));
		pathResult->size = 2;
		pathResult->capacity = 2;
		pathResult->vector = malloc(2*sizeof(PIECES));

		if(tipo == 1){
			for(int i = 2; i < 4; i++){
				if(validar(tab, Xposition + pathX[i], Yposition + pathY[i]) == 0){
					pathResult->vector[i-2].column = Xposition + pathX[i];
					pathResult->vector[i-2].line = Yposition + pathY[i];
				}else{
					pathResult->vector[i-2].column = 0;
					pathResult->vector[i-2].line = 0;
				}
			}
		}

			if(tipo == 2){
				for(int i = 0; i < 2; i++){
					if(validar(tab, Xposition + pathX[i], Yposition + pathY[i]) == 0){
						pathResult->vector[i].column = Xposition + pathX[i];
						pathResult->vector[i].line = Yposition + pathY[i];
					}else{
						pathResult->vector[i].column = 0;
						pathResult->vector[i].line = 0;
					}
				}
		}

		return selectiveClean(pathResult);

	}else if(classe == 2){

		DYNAMICVEC *pathResult = malloc(sizeof(DYNAMICVEC));
		pathResult->size = (COL_MAX - 1)*4;
		pathResult->capacity = (COL_MAX - 1)*4;
		pathResult->vector = calloc((COL_MAX - 1)*4, sizeof(PIECES));

		for(int i = 0; i < 4; i++)
				for(int z = 1; z <= COL_MAX ;z++){
					if(validar(tab, Xposition + z*pathX[i], Yposition + z*pathY[i]) == 0){
						pathResult->vector[(z-1)*4 +i].column = Xposition + z*pathX[i];
						pathResult->vector[(z-1)*4 +i].line = Yposition + z*pathY[i];
					}else{
						break;
					}
				}

		return selectiveClean(pathResult);


	}else if(classe <= 0)
		return NULL;

}


DYNAMICVEC *posicaoDamas (BOARD *tab, int coluna, int linha, PATH *pedrascomidas){
	DYNAMICVEC *pathResult = malloc(sizeof(DYNAMICVEC));
	pathResult->size = 0;
	pathResult->capacity = 2;
	pathResult->vector = calloc(COL_MAX,sizeof(PIECES));

	int i, dirX, dirY, c_final, l_final;

	for (i = 0; pedrascomidas[i+1].posXcomida != 0 || pedrascomidas[i+1].posYcomida != 0; i++){};


	dirX = pedrascomidas[i].posXfinal - pedrascomidas[i].posXcomida;
	dirY = pedrascomidas[i].posYfinal - pedrascomidas[i].posYcomida;

	c_final = pedrascomidas[i].posXfinal;
	l_final = pedrascomidas[i].posYfinal;

	BOARD vet[COL_MAX*LIN_MAX];
	int aux;
	for (int l = 0; l < LIN_MAX; l++)
		for (int c = 0; c < COL_MAX; c++)
			vet[l*COL_MAX+c].tipo = tab[l*COL_MAX+c].tipo;

	vet[POS].tipo = 0;
	vet[POS].classe = 0;



	for (i = 0; i < COL_MAX; i++){
		if (validar(vet, c_final+(i*dirX), l_final+(i*dirY))){
			break;
		} else {
			pathResult->vector[i].column = c_final+(i*dirX);
			pathResult->vector[i].line = l_final+(i*dirY);
			pathResult->size += 1;
		}
	}

	return pathResult;
}

//DAR FREE!!!!!!!!!!!!!!!!!!!!!!!!
DYNAMICVEC *selectiveClean(DYNAMICVEC *vector){
	
  int counter = 0;
  for(int i = 0; i < vector->size; i++)
    if(vector->vector[i].column != 0 || vector->vector[i].line != 0)
      counter++;

  DYNAMICVEC *pathResult = malloc(sizeof(DYNAMICVEC));
  pathResult->size = counter;
  pathResult->capacity = counter;
  pathResult->vector = calloc(counter, sizeof(PIECES));

  for(int i = 0, j = 0; i < vector->size; i++){
    if(vector->vector[i].column != 0 || vector->vector[i].line != 0){
      pathResult->vector[j].column = vector->vector[i].column;
      pathResult->vector[j].line = vector->vector[i].line;
      j++;
    }
  }

	return pathResult;
}

int validatePlay(BOARD *tab, int c_destino, int l_destino, DYNAMICVEC *teste){
	for(int i = 0; i < teste->size; i++)
		if(teste->vector[i].column == c_destino && teste->vector[i].line == l_destino)
			return 1;

	for(int i = 0; i < teste->size; i++)
			printf("possibilidade %d: %c %d\n", i, teste->vector[i].column + 'A',  teste->vector[i].line + 1);

	return 0;

}
