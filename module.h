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




