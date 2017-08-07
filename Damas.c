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

			/*	while (1){	// pede as coordenadas de ORIGEM da pedra a ser movida, em seguida checa se estao no intervalo correto e se essa coordenada representa o local de uma pedra
							while (1){
								printf ("Digite a coluna da pedra a ser movida: ");
								scanf (" %d", &c_origem);
							    getchar();

								c_origem--;
								if (c_origem >= COL_MAX || c_origem < 0)
									printf ("Coluna invalida, tente novamente\n");
								else
									break;
							}

							while (1){
								printf ("Digite a linha da pedra a ser movida: ");
								scanf (" %d", &l_origem);
								getchar();

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
						scanf (" %d", &c_destino);
						getchar();
						c_destino--;
						if (c_destino >= COL_MAX || c_destino < 0)
							printf ("Coluna invalida, tente novamente\n");
						else
							break;
					}

					while (1){
						printf ("Digite a linha de destino: ");
						scanf (" %d", &l_destino);
						getchar();
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
			*/

			while (1){
				printf ("ex ('A6 C4' move pedra de A6 para C4): ");
				fgets (input, 10, stdin);
				input[0] = tolower(input[0]);
				input[3] = tolower(input[3]);

				c_origem = input[0] - 'a';
				l_origem = input[1] - '1';

				c_destino = input[3] - 'a';
				l_destino = input[4] - '1';

				if (validar(tab, c_origem, l_origem) == turno  && validar(tab, c_destino, l_destino) == 0)
					break;
				else{
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
					printf("Opcao unica: (%c%c)\n", usefulPieces[usefulPiecesParameters.size - 1].column + 'a', usefulPieces[usefulPiecesParameters.size - 1].line + '1');
					printf("Aperte enter para continuar\n");
					getchar();
					c_origem = usefulPieces[usefulPiecesParameters.size - 1].line;
					l_origem =	usefulPieces[usefulPiecesParameters.size - 1].column;


				}else{

					int choice = 0;
					printf("Escolha a opcao correspondente à peça que deseja usar para comer:\n");
					for(int i = 0; i < usefulPiecesParameters.size; i++){
						printf("%d - %c%c\n",i+1 , usefulPieces[i].line + 'a' , usefulPieces[i].column + '1');
					}
					printf("Digite:\n");
					scanf(" %d", &choice);
					getchar();
					choice--;
					if(choice < usefulPiecesParameters.size){
						c_origem = usefulPieces[choice].line;
						l_origem =	usefulPieces[choice].column;
					}else{
						printf("opcao invalida\n");
						continue;
					}
				}

				free(usefulPieces);
				usefulPiecesParameters.capacity = 0;
				usefulPiecesParameters.size = 0;

				if (validar(tab, c_origem, l_origem) == turno)
					break;
				else{
					printf ("entrada invalida\n");
				}
			}

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

			for (int i = 0; i < 100; i++){
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

			scanf (" %d", &track);
			getchar();
			track--;
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
				while(1){
					while (1){
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
					scanf (" %d", &l_destino);
					getchar();
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
