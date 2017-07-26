#include <stdio.h>
#include <stdlib.h>
#include "module.h"
#include "func_declarations.h"

int game = 1;
int turno = 2;  //a vez de qual jogador, inicializar com o valor do primeiro jogador

BOARD *GAME (int c_origem, int l_origem, int c_destino, int l_destino, PATH *pedrascomidas){
	static int jogoiniciou = 0;     //inicializa tabuleiro somente uma vez
	static BOARD *tabuleiro;


	if (!jogoiniciou){
		tabuleiro = calloc (COL_MAX*LIN_MAX, sizeof(BOARD));
		posicionarpedras(tabuleiro);

/*
		int vet[COL_MAX*LIN_MAX] = {0, 0, 0, 0, 0, 0, 0, 0,
									0, 0, 0, 0, 2, 0, 2, 0,
									0, 0, 0, 0, 0, 0, 0, 0,
									0, 0, 0, 0, 2, 0, 2, 0,
									0, 0, 0, 0, 0, 0, 0, 0,
									0, 0, 2, 0, 2, 0, 0, 0,
									0, 0, 0, 1, 0, 0, 0, 0,
									0, 0, 0, 0, 0, 0, 0, 0,
									};

		for (int linha = 0; linha < LIN_MAX; linha++)
			for (int coluna = 0; coluna < COL_MAX; coluna++)
				tabuleiro[POS].tipo = vet[POS];

*/
		

		jogoiniciou = 1;
		system ("tput reset");
		imprimir(tabuleiro);
	}


	if (c_origem == l_origem && l_origem == c_destino && c_destino == l_destino){
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

	system ("tput reset");
	imprimir(tabuleiro);
	return tabuleiro;
}



int main (){
	int i, j;
	int c_origem = 0, l_origem = 0, c_destino = 0, l_destino = 0;
	int track = 0; //caminho escolhido pelo jogador para comer as pedras
	char acao;
	BOARD *tab = NULL;

	tab = GAME (0,0,0,0,NULL);

	while (game == 1){

		printf ("Mover ou Capturar? (M/C): ");
		scanf (" %c", &acao);

		if (acao == 'M' || acao == 'm'){
			while (1){	// pede as coordenadas de ORIGEM da pedra a ser movida, em seguida checa se estao no intervalo correto e se essa coordenada representa o local de uma pedra
					while (1){
						printf ("Digite a coluna da pedra a ser movida: ");
						scanf ("%d", &c_origem);
						c_origem--;
						if (c_origem >= COL_MAX || c_origem < 0)
							printf ("Coluna invalida, tente novamente\n");
						else
							break;
					}

					while (1){
						printf ("Digite a linha da pedra a ser movida: ");
						scanf ("%d", &l_origem);
						l_origem--;
						if (l_origem >= COL_MAX || l_origem < 0)
							printf ("Linha invalida, tente novamente\n");
						else
							break;
					}

					if (tab[l_origem*COL_MAX+c_origem].tipo == 0)  // A coordenada indicada esta vazia
						printf ("Nao tem pedra em Coluna: %d, Linha: %d\nDigite uma posicao valida\n", c_origem+1, l_origem+1);
					else
						break;
			}
			while (1){	// pede as coordenadas de DESTINO da pedra a ser movida, em seguida checa se ja existe uma pedra nesse local
				while ( 1){
					printf ("Digite a coluna de destino: ");
					scanf ("%d", &c_destino);
					c_destino--;
					if (c_destino >= COL_MAX || c_destino < 0)
						printf ("Coluna invalida, tente novamente\n");
					else
						break;
				}

				while (1){
					printf ("Digite a linha de destino: ");
					scanf ("%d", &l_destino);
					l_destino--;
					if (l_destino >= COL_MAX || l_destino < 0)
						printf ("Coluna invalida, tente novamente\n");
					else
						break;
				}

				if (tab[l_destino*COL_MAX+c_destino].tipo != 0)  // A coordenada indicada esta ocupada, a pedra nao podera ser movida para ca
					printf ("Ja tem uma pedra en Coluna: %d, Linha: %d\nDigite uma posicao valida\n", c_origem+1, l_origem+1);
				else if ((l_destino+1)*(c_destino+1) % 2 != 0)
					printf ("Local de destino invalido. Digite uma posicao valida\n");
				else
					break;
			} //Loop de movimento

			tab = GAME (c_origem, l_origem, c_destino, l_destino, NULL);
		}

		else if (acao == 'C' || acao == 'c'){ //loop de captura
			printf ("digite x origem: ");
			scanf ("%d", &c_origem);
			c_origem--;
			printf ("digite y origem: ");
			scanf ("%d", &l_origem);
			l_origem--;

			PATH **maiorcaminho = NULL;

			maiorcaminho = EncontrarCaminho (tab, c_origem, l_origem, tab[l_origem*COL_MAX+c_origem].tipo, -1);

			printf ("Escolha o caminho a ser serguido: \n");
			
			for (int i = 0; i < 100; i++){
				if (maiorcaminho[i][0].posXcomida == 0 && maiorcaminho[i][0].posYcomida == 0){
					//printf ("morreu aqui 2\n");
						break;
					}
				printf ("caminho %d\n", i+1);
				for (int j = 0; j<20; j++){
					if (maiorcaminho[i][j].posXcomida == 0 && maiorcaminho[i][j].posYcomida == 0){
						//printf ("morreu aqui 3\n");
						break;
					}
					else
						printf ("passa por (%d, %d), come (%d, %d) ", maiorcaminho[i][j].posXfinal + 1, maiorcaminho[i][j].posYfinal + 1, maiorcaminho[i][j].posXcomida + 1, maiorcaminho[i][j].posYcomida + 1);
				}
				printf ("\n"); // imprime os caminhos
			}

			scanf ("%d", &track);
			track--;
			for (i = 0; i< 100; i++){
				if (maiorcaminho[track][i].posXcomida == 0 && maiorcaminho[track][i].posYcomida == 0){	
					i--;
					break;
				}
			}
			
			tab = GAME (c_origem, l_origem, maiorcaminho[track][i].posXfinal, maiorcaminho[track][i].posYfinal, maiorcaminho[track]);
			free (maiorcaminho);


		}

		else {
			printf ("entrada invalida\n");
			getchar ();
			getchar ();
		}

		


	}
}
