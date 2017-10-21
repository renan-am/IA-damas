#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "src/module.h"
#include "src/func_declarations.h"

int game = 1;
int turno = 2;

void DrawBoard (Color *colors, int *mouseLocal){
	 	for (int i = 0; i < 8; i++)
      		  for (int j = i%2; j < 8; j+=2)
	            {
	               		DrawRectangle(j*80, i*80, 80, 80, colors[0]);  
	                	
	            }

 		for (int i = 0; i < 8; i++)
        	for (int j = (i+1)%2; j < 8; j+=2)
        		{
        			if (mouseLocal[1] == i && mouseLocal[0] == j)
	               		DrawRectangle(j*80+5, i*80+5, 70, 70, GRAY);  
	                else 
	               		DrawRectangle(j*80, i*80, 80, 80, colors[1]);  
        		}
}		

void DrawPieces (BOARD *tab){
	for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
        	if (tab[i*8+j].tipo == 1)
        		DrawCircle( j*80+40,i*80+40, 35, RED);
        	else if (tab[i*8+j].tipo == 2)
        		DrawCircle( j*80+40,i*80+40, 35, GREEN);
        }
        
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 640;
    int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "Damas");

	int c_origem = -100, l_origem = -100, c_destino = -100, l_destino = -100;

	BOARD *tab = NULL;
	tab = GAME (0,0,0,0,NULL);

    Color colors[3] = {WHITE, DARKGRAY, BLUE};


    int mouseLocal[2];
    mouseLocal[0] = 0;
    mouseLocal[1] = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        mouseLocal[0] = GetMouseX()/80;
        mouseLocal[1] = GetMouseY()/80;

       if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        	if (c_origem == -100 && l_origem == -100){
        		if (tab[mouseLocal[1]*8+mouseLocal[0]].tipo > 0){
		        	c_origem = mouseLocal[0];
		        	l_origem = mouseLocal[1];
		        } else {
	        		c_origem = -100;
	        		l_origem = -100;
	        	}
        	} else {
        		if (tab[mouseLocal[1]*8+mouseLocal[0]].tipo == 0){
        			printf ("pegou destino\n");
		        	c_destino = mouseLocal[0];
		        	l_destino = mouseLocal[1];
		        } else {
	        		c_origem = -100;
					l_origem = -100;
	        	}
        	}
        printf ("%d %d %d %d\n", c_origem, l_origem, c_destino, l_destino);
       }
       if (c_origem != -100 && l_origem != -100 && c_destino != -100 && l_destino != -100){
       		printf ("moveu\n");
       		tab = GAME( c_origem,  l_origem,  c_destino,  l_destino, NULL);
       		c_origem = -100;
			l_origem = -100;
			c_destino = -100;
			l_destino = -100;
       }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLUE);

	       	DrawBoard(colors, mouseLocal);
	       	DrawPieces(tab);  

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}