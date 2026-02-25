#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "tetris.h"





// void FreeMatrix(int** matrix){
//     if (matrix != NULL){
//             for(int i = 0; i < rows; i++){
//             free(matrix[i]);
//         }
//         free(matrix);
//     }
//     matrix = NULL;
// }







// void RenderUserInterface(){
//     srand(time(NULL)); 

//     // noecho();      ???                 
//     //  if (win1 == NULL) { // нужна ли?
//     //     endwin();
//     //     printf("error of making win!\n");
//     //     return 1;
//     // }

//     // FigureInfo_t* game_sesion;
//     // InitFigure(game_sesion);

//     // int random_num = GenerateRandomNum(MAX_NUM_FIGURES); 
//     // GenerateFigure(random_num, game_sesion->current_figure);


//     //int center_width = (win_width / 2) - 1 - CELL_SIZE; // пока хз насчет центровки

//     //print_figure(*game_sesion, win, center_width);
                 
//     wrefresh(win);
//     getch();
//     endwin();
// }

























// void print_figure(FigureInfo_t *game_sesion, WINDOW* win){
//     for(int i = 0; i < 4; i++) {
//         for(int j = 0; j < 4; j++) {
//             if(game_sesion->current_figure[i][j] == 1) {
//                 mvwprintw(win, i + FRAME_LINE, center_width + (j * CELL_SIZE) + FRAME_LINE, "[ ]"); 
//             }                                   
//         }
//     }  

// }

// CENTER_WIDTH 




// пишу функцию печати фигуры 
// когда появляется фигура она должна быть наверзу в центре -- координаты по умолчанию 
// если будет действия вправо влево то координаты смещаются