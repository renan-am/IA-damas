#include <stdio.h>
#include "module.h"

PATH *possiblePaths = calloc(100*100, sizeof(PATH)); // alocar uma matriz caminho de 100x100 com o do tipo PATH.


void PossiblePaths(int posAtualX , int posAtualY){

	if(checarSeCome(posAtualX, posAtualY, posAtualX +1, posAtualY +1)){
	
		

	}else if(checarSeCome(posAtualX, posAtualY, posAtualX -1, posAtualY +1)){



	}else if(checarSeCome(posAtualX, posAtualY, posAtualX +1, posAtualY -1)){



	}else if(checarSeCome(posAtualX, posAtualY, posAtualX -1, posAtualY -1){



	}
}