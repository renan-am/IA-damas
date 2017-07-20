#include "possiblePaths.c"
#include "funcoes_do_jogo.c"

#define COL_MAX 8
#define LIN_MAX 8
#define POS linha*COL_MAX+coluna

typedef struct {

	int posXfinal;
	int posYfinal;
	int posXcomida;
	int posYcomida;

} PATH;

typedef struct {

	int tipo;
	int energia;

} BOARD;



extern BOARD *tabuleiro;
extern int game; 



void PossiblePaths(int posAtualX , int posAtualY);


void posicionarpedras ();


void mover (int c_origem, int l_origem, int c_destino, int l_destino);


int checarSeCome (int c_origem, int l_origem, int c_alvo, int l_alvo);


void imprimir ();