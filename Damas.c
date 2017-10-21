#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "module.h"
#include "func_declarations.h"

int game = 1;
int turno = 2;  //a vez de qual jogador, inicializar com o valor do primeiro jogador


int main (){
	int i, j;
	int c_origem = 0, l_origem = 0, c_destino = 0, l_destino = 0;
	int track = 0; //caminho escolhido pelo jogador para comer as pedras
	char acao;
	char input[10] = "0";
	BOARD *tab = NULL;
	PIECES *usefulPieces = NULL;
	DYNAMICVEC usefulPiecesParameters;
	usefulPiecesParameters.capacity = 0;
	usefulPiecesParameters.size = 0;

	tab = GAME (0,0,0,0,NULL);

	while (game == 1){

		printf ("Turno do Jogador: %d\n", turno);
		//printf ("Mover ou Capturar? (M/C): ");
		//scanf (" %c", &acao);

		acao = checarJogada (tab, turno, &usefulPieces, &usefulPiecesParameters);

		if (acao == 'm')
			printf ("Por favor escolha pedra a ser movida\n");
		else if (acao == 'c')
			printf ("Por favor escolha pedra que ira realizar a captura\n");
		else{
			printf ("Jogador %d, nao possui jogadas validas\n", turno);
			turno = (turno%2)+1;
			continue;
		}

		if (acao == 'M' || acao == 'm'){
			DYNAMICVEC *teste = NULL;
			while (1){
				printf ("ex ('A6 B5' move pedra de A6 para B5): ");
				fgets (input, 10, stdin);

				if (strlen(input) != 6){
					printf ("entrada invalida, por favor escreva no formato 'A1 B2'\n");
					continue;
				}

				input[0] = tolower(input[0]);
				input[3] = tolower(input[3]);

				c_origem = input[0] - 'a';
				l_origem = input[1] - '1';

				c_destino = input[3] - 'a';
				l_destino = input[4] - '1';

				if (validar(tab, c_origem, l_origem) == turno ){
					teste = goodPaths(tab, c_origem, l_origem, tab[l_origem*COL_MAX+c_origem].classe, tab[l_origem*COL_MAX+c_origem].tipo);
					if(validatePlay(tab, c_destino, l_destino, teste) == 1)
						break;
				}else{
					printf ("entrada invalida\n");
				}
			}

			tab = GAME (c_origem, l_origem, c_destino, l_destino, NULL);
		}

		else if (acao == 'C' || acao == 'c'){ //loop de captura
			/*printf ("digite x origem: ");
			scanf ("%d", &c_origem);
			c_origem--;
			printf ("digite y origem: ");
			scanf ("%d", &l_origem);
			l_origem--;*/

			while (1){
				printf("Existe(m) peça(s) que são obrigada(s) a realizar a ação de comer:\n");
				//printf("%d %d\n\n",usefulPieces[usefulPiecesParameters.size - 1].column, usefulPieces[usefulPiecesParameters.size - 1].line);
				if(usefulPiecesParameters.size == 1){
					printf("Opcao unica: %c%c\n", usefulPieces[usefulPiecesParameters.size - 1].column + 'A', usefulPieces[usefulPiecesParameters.size - 1].line + '1');
					printf("Aperte enter para continuar\n");
					getchar();
					c_origem = usefulPieces[usefulPiecesParameters.size-1].column;
					l_origem = usefulPieces[usefulPiecesParameters.size-1].line;
				}else{
					int choice = 0;
					printf("Escolha a opcao correspondente à peça que deseja usar para comer:\n");
					for(int i = 0; i < usefulPiecesParameters.size; i++){
						printf("%d - %c%c\n",i+1 , usefulPieces[i].column + 'A', usefulPieces[i].line + '1');
					}
					printf("Digite:\n");
					scanf(" %d", &choice);
					getchar();
					choice--;

						if(choice < usefulPiecesParameters.size){
								c_origem = usefulPieces[choice].column;
								l_origem = usefulPieces[choice].line;
						}else{
								printf("opcao invalida\n");
								continue;
							}
				}



				if (validar(tab, c_origem, l_origem) == turno)
					break;
				else{
					printf ("entrada invalida\n");
				}
			}

			free(usefulPieces);
			usefulPieces = NULL;
			usefulPiecesParameters.capacity = 0;
			usefulPiecesParameters.size = 0;

			PATH **maiorcaminho = NULL;

			if (tab[l_origem*COL_MAX+c_origem].classe == 1)
				maiorcaminho = EncontrarCaminho (tab, c_origem, l_origem, tab[l_origem*COL_MAX+c_origem].tipo, -1);
			else if (tab[l_origem*COL_MAX+c_origem].classe == 2)
				maiorcaminho = EncontrarCaminhoDama (tab, c_origem, l_origem, tab[l_origem*COL_MAX+c_origem].tipo, -1);
			else {
				printf ("erro\n");
				continue;
			}

			if (!maiorcaminho){
				printf ("Essa pedra nao come nada\n");
				continue;
			}

			printf ("Escolha o caminho a ser serguido: \n");

			for (i = 0; i < 100; i++){
				if (maiorcaminho[i][0].posXcomida == 0 && maiorcaminho[i][0].posYcomida == 0){
					//printf ("morreu aqui 2\n");
						break;
					}
				printf ("caminho %d:  ", i+1);
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

			while (1){
				scanf (" %d", &track);
				getchar();
					if (track > i){
						printf ("caminho inválido, tente de novo: ");
						continue;
					}
				track--;
				break;
			}

			for (i = 0; i< 100; i++){
				if (maiorcaminho[track][i].posXcomida == 0 && maiorcaminho[track][i].posYcomida == 0){
					i--;
					break;
				}
			}

			if (tab[l_origem*COL_MAX+c_origem].classe == 1){
				tab = GAME (c_origem, l_origem, maiorcaminho[track][i].posXfinal, maiorcaminho[track][i].posYfinal, maiorcaminho[track]);
				free (maiorcaminho);
			}
			else if (tab[l_origem*COL_MAX+c_origem].classe == 2){
				while (1){
					printf ("Escolha casa de destino da Dama após a ação de comer\nex ('C4' irá parar na casa C4): ");
					fgets (input, 10, stdin);
					input[0] = tolower(input[0]);

					c_destino = input[0] - 'a';
					l_destino = input[1] - '1';
					DYNAMICVEC *teste;
					teste = posicaoDamas (tab, c_origem, l_origem, maiorcaminho[track]);
					for(int i = 0; i < teste->size; i++)
						printf("possibilidade %d: %c %d\n", i, teste->vector[i].column + 'A',  teste->vector[i].line + 1);
					int parada;
					scanf("%d", &parada);

					if (validar(tab, c_origem, l_origem) == turno  && validar(tab, c_destino, l_destino) == 0)
						break;
					else{
						printf ("entrada invalida\n");
					}
				}
				tab = GAME (c_origem, l_origem, c_destino, l_destino, maiorcaminho[track]);
				free (maiorcaminho);
			}
		}else{
			printf ("entrada invalida\n");
			getchar ();
			getchar ();
		}




	}
}
