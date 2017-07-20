#include "possiblePaths.c"
#include "funcoes_do_jogo.c"

typedef struct{

	int posXfinal;
	int posYfinal;
	int posXcomida;
	int posYcomida;

} PATH;

typedef struct {
	int tipo;
	int energia;
}	BOARD;

void PossiblePaths(int posAtualX , int posAtualY);
