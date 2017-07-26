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

	int tipo;     // 0: vazio      1: pedra do jogador 1 (superior)   2: pedra do jogador 2 (inferior)
	int classe; 	//1: pedra comum      2: dama
	int potencial;

} BOARD;



extern int game;
extern int turno;



extern PATH **waysToWin;



