#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "src/module.h"
#include "src/func_declarations.h"

int game = 1;
int turno = 2;

void DrawBoard (Color *colors, int *mouseLocal, DYNAMICVEC *jogadas){
 	for (int i = 0; i < 8; i++)
  		  for (int j = i%2; j < 8; j+=2)
            {
               		DrawRectangle(j*80, i*80, 80, 80, colors[0]);
            }

		for (int i = 0; i < 8; i++)
    	for (int j = (i+1)%2; j < 8; j+=2)
    		{
    			if (mouseLocal[1] == i && mouseLocal[0] == j){
               		DrawRectangle(j*80, i*80, 80, 80, BLUE);
                    DrawRectangle(j*80+5, i*80+5, 70, 70, GRAY);
                }
                else 
               		DrawRectangle(j*80, i*80, 80, 80, colors[1]);  
    		}
}		

void DrawPieces (BOARD *tab){
	for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
        	if (tab[i*8+j].tipo == 1){
                if (tab[i*8+j].classe == 1)
        		    DrawCircle( j*80+40,i*80+40, 35, RED);
                if (tab[i*8+j].classe == 2){
                    DrawCircle( j*80+40,i*80+40, 35, YELLOW);
                    DrawCircle( j*80+40,i*80+40, 25, RED);

                }
            }
        	else if (tab[i*8+j].tipo == 2){
        		if (tab[i*8+j].classe == 1)
                    DrawCircle( j*80+40,i*80+40, 35, GREEN);
                if (tab[i*8+j].classe == 2){
                    DrawCircle( j*80+40,i*80+40, 35, YELLOW);
                    DrawCircle( j*80+40,i*80+40, 25, GREEN);

                }
            }
        }  
}

void DrawMoveHighlights (int c_origem, int l_origem, Color *colors, int *mouseLocal, DYNAMICVEC *jogadas){
    if (jogadas){
        for (int i = 0; i < jogadas->size; i++){
            DrawRectangle(jogadas->vector[i].column*80, jogadas->vector[i].line*80, 80, 80, BLUE);
            DrawRectangle(jogadas->vector[i].column*80+5, jogadas->vector[i].line*80+5, 70, 70, colors[1]);  

            if (mouseLocal[1] == jogadas->vector[i].line && mouseLocal[0] == jogadas->vector[i].column)
                DrawRectangle(jogadas->vector[i].column*80+5, jogadas->vector[i].line*80+5, 70, 70, GRAY);
        }
    }

    DrawRectangle(c_origem*80, l_origem*80, 80, 80, SKYBLUE);
    DrawRectangle(c_origem*80+5, l_origem*80+5, 70, 70, colors[1]);  

    if (mouseLocal[1] == l_origem && mouseLocal[0] == c_origem)
        DrawRectangle(c_origem*80+5, l_origem*80+5, 70, 70, GRAY);
}

void DrawPiecesHighlights (Color *colors, int *mouseLocal, PIECES *pieces, DYNAMICVEC piecesParameters){
    if (pieces){
         for (int i = 0; i < piecesParameters.size; i++){
            DrawRectangle(pieces[i].column*80, pieces[i].line*80, 80, 80, PINK);
            DrawRectangle(pieces[i].column*80+5, pieces[i].line*80+5, 70, 70, colors[1]);  

            if (mouseLocal[1] == pieces[i].line && mouseLocal[0] == pieces[i].column)
                DrawRectangle(pieces[i].column*80+5, pieces[i].line*80+5, 70, 70, GRAY);
        }
    }
}

void DrawTargetHighlights (BOARD *tab, int c_origem,int l_origem, Color *colors, int *mouseLocal, DYNAMICVEC *jogadas){
     if (jogadas){
        for (int i = 0; i < jogadas->size; i++){
            if (tab[jogadas->vector[i].line*8+jogadas->vector[i].column].tipo > 0){
               DrawLine(jogadas->vector[i].column, jogadas->vector[i].line, jogadas->vector[i].column + 80, jogadas->vector[i].line + 80, BLACK);
               DrawLine(jogadas->vector[i].column + 80, jogadas->vector[i].line, jogadas->vector[i].column, jogadas->vector[i].line + 80, BLACK);
            }



            DrawRectangle(jogadas->vector[i].column*80, jogadas->vector[i].line*80, 80, 80, BLUE);
            DrawRectangle(jogadas->vector[i].column*80+5, jogadas->vector[i].line*80+5, 70, 70, colors[1]);  

            if (mouseLocal[1] == jogadas->vector[i].line && mouseLocal[0] == jogadas->vector[i].column)
                DrawRectangle(jogadas->vector[i].column*80+5, jogadas->vector[i].line*80+5, 70, 70, GRAY);
        }
    }

    DrawRectangle(c_origem*80, l_origem*80, 80, 80, SKYBLUE);
    DrawRectangle(c_origem*80+5, l_origem*80+5, 70, 70, colors[1]);  

    if (mouseLocal[1] == l_origem && mouseLocal[0] == c_origem)
        DrawRectangle(c_origem*80+5, l_origem*80+5, 70, 70, GRAY);
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 640;
    int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "Damas");
    
    Color colors[3] = {WHITE, DARKGRAY, BLUE};

    int c_origem = -100, l_origem = -100, c_destino = -100, l_destino = -100;

    BOARD *tab = NULL;
    tab = GAME (0,0,0,0,NULL,1);

    
    PIECES *usefulPieces = NULL;
    DYNAMICVEC usefulPiecesParameters;
    usefulPiecesParameters.capacity = 0;
    usefulPiecesParameters.size = 0;
    char acao;

    DYNAMICVEC *jogadas = NULL;
    DYNAMICVEC *paths = NULL;
    DYNAMICVEC *destinos = NULL;

    PATH **caminho = NULL;

    int mouseLocal[2];
    mouseLocal[0] = 0;
    mouseLocal[1] = 0;

    int select = 0;


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        mouseLocal[0] = GetMouseX()/80;
        mouseLocal[1] = GetMouseY()/80;

        acao = checarJogada (tab, turno, &usefulPieces, &usefulPiecesParameters);
        
        if (acao == 'm'){
           if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if (c_origem == -100 && l_origem == -100){
                    if (tab[mouseLocal[1]*8+mouseLocal[0]].tipo == turno){
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
                        jogadas = NULL;
                    }
                }
                printf ("origem (x:%d,y:%d) destino (x:%d,y:%d)\n", c_origem, l_origem, c_destino, l_destino);
           }

           if (c_origem != -100 && l_origem != 100){
                jogadas = goodPaths(tab, c_origem, l_origem, tab[l_origem*COL_MAX+c_origem].classe, tab[l_origem*COL_MAX+c_origem].tipo);
           }

           if (c_origem != -100 && l_origem != -100 && c_destino != -100 && l_destino != -100){
                if (validatePlay(tab, c_destino, l_destino, jogadas))
                    tab = GAME( c_origem,  l_origem,  c_destino,  l_destino, NULL, 1);
                c_origem = -100;
                l_origem = -100;
                c_destino = -100;
                l_destino = -100;
                jogadas = NULL;
           }
            
            //----------------------------------------------------------------------------------

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

                ClearBackground(RAYWHITE);

                DrawBoard(colors, mouseLocal, jogadas);
                DrawMoveHighlights(c_origem, l_origem, colors, mouseLocal, jogadas);
                DrawPieces(tab);  

            EndDrawing();
        } else if (acao == 'c') {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if (c_origem == -100 && l_origem == -100){
                    if (tab[mouseLocal[1]*8+mouseLocal[0]].tipo == turno  
                            &&  validateSelection(tab, mouseLocal[0], mouseLocal[1], usefulPiecesParameters, usefulPieces)){

                        c_origem = mouseLocal[0];
                        l_origem = mouseLocal[1];

                        select = 1;

                        if (tab[l_origem*COL_MAX+c_origem].classe == 1)
                            caminho = EncontrarCaminho (tab, c_origem, l_origem, tab[l_origem*COL_MAX+c_origem].tipo, -1);
                        else if (tab[l_origem*COL_MAX+c_origem].classe == 2)
                            caminho = EncontrarCaminhoDama (tab, c_origem, l_origem, tab[l_origem*COL_MAX+c_origem].tipo, -1);

                        paths = translatetoDYN(caminho);
                        destinos = destinosDYN(caminho);

                    } else {
                        c_origem = -100;
                        l_origem = -100;
                    }
                } else {
                    if (1 == 1){
                        printf ("pegou destino\n");
                        c_destino = mouseLocal[0];
                        l_destino = mouseLocal[1];
                    } else {
                        c_origem = -100;
                        l_origem = -100;
                        paths = NULL;
                    }
                }
                printf ("origem (x:%d,y:%d) destino (x:%d,y:%d)\n", c_origem, l_origem, c_destino, l_destino);
            }

            if (c_origem != -100 && l_origem != -100 && c_destino != -100 && l_destino != -100){
                if (validatePlay(tab, c_destino, l_destino, paths)){
                    int track = findTrack (c_destino, l_destino, caminho);
                    printf ("track = %d\n", track);
                    if (track > -1)
                        tab = GAME( c_origem,  l_origem,  c_destino,  l_destino, caminho[track], 1);
                }
                c_origem = -100;
                l_origem = -100;
                c_destino = -100;
                l_destino = -100;
                paths = NULL;
                usefulPieces = NULL;
                usefulPiecesParameters.capacity = 0;
                usefulPiecesParameters.size = 0;
                select = 0;
                //checarJogada (tab, turno, &usefulPieces, &usefulPiecesParameters);
            }




            BeginDrawing();

                ClearBackground(RAYWHITE);

                DrawBoard(colors, mouseLocal, paths);
                
                if (select)
                    DrawTargetHighlights(tab, c_origem, l_origem, colors, mouseLocal, paths);
                else
                    DrawPiecesHighlights(colors, mouseLocal, usefulPieces, usefulPiecesParameters);

                DrawPieces(tab);  

            EndDrawing();
        } else {
            break;
        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}