#include "common.h"
#include <ncurses.h>
#include "backend.h"

WINDOW* InitGameFieldFront(){
    WINDOW *win = newwin(GAME_WIN_HEIGHT, GAME_WIN_WIDTH, 0, 0);
    box(win, 0, 0);
    refresh();
    return win;
}

void InitNcurses() {
    initscr();
    keypad(stdscr, TRUE);
    noecho(); 
    curs_set(0); 
    nodelay(stdscr, TRUE);   
}

void PrintGameFieldFront(GameInfo_t game, WINDOW* game_win, int action){ 
    for(int i = 0; i < FIELD_HEIGHT; i++) {
        for(int j = 0; j < FIELD_WIDTH; j++) {
            int width = j * CELL_SIZE + FRAME_LINE;
            int height = i + FRAME_LINE;   
            if(game.field[i][j] == 1) {
                mvwprintw(game_win, height, width, "[ ]");         
            } else {
                mvwprintw(game_win, height, width, "   ");          
            }                        
        }
    }  
    wrefresh(game_win);
}


void PlayTetris(){
    WINDOW* game_win = InitGameFieldFront();
    int tick = 0;
    int n = 0;
    while(1){
    int key = getch();
    int action = -1;
    bool hold = 0;
    switch(key){
            // case KEY_ENTER:
            //     action = Start;
            //     userInput(Start, hold);
            //     break;

            case 10: // ДОБАВИТЬ В DEFINEE 
                userInput(Start, hold);
                break;

            case KEY_RIGHT:
                userInput(Right, hold);

                break; 

            case KEY_LEFT:
                userInput(Left, hold);
                break;

            case KEY_DOWN:
                userInput(Down, hold);
                break;
            
        }    
        if (tick >= 20) {         // ~ 20 * 10ms = 200ms
            GameInfo_t game = updateCurrentState();
            PrintGameFieldFront(game, game_win, action);
            tick = 0;
        }
        napms(20); 
        tick++;
    }
}

int main() {
    InitNcurses();
    PlayTetris();
    endwin();

    return 0;
}










// int main (){

   
//     GameState_t state = Initial;
//     GameInfo_t* game = GetGameInfo();
//     InitGameInfo(game);
//     GenerateNewFigure(figure);

//     int move_down_status = -1;
//     int key = 0;
//     struct timespec last_tick = {0}; // вынести в отдельную структуру?
//     struct timespec now = {0}; // вынести в отдельную структуру?
//     long time_interval =  0;
//     clock_gettime(CLOCK_MONOTONIC, &last_tick); //текущее время в ласт тик 
//     while(state != GameOver){
//         struct timespec now;
//         clock_gettime(CLOCK_MONOTONIC, &now);
//         int tick_time = 500; 
//         time_interval = (now.tv_nsec - last_tick.tv_nsec) / 1000000 + (now.tv_sec - last_tick.tv_sec) * 1000;
//         if(time_interval >= tick_time){
//             if(MoveDown(game, figure) == MoveDownCollision){
//                 // после генерации новой фигуры скинуть таймер!!!
//             } 
//             last_tick = now;
//         }
//         key = getch();
//         switch(key){
//             case KEY_RIGHT:
//                 MoveRight(game, figure);
//                 // возвращать статус коллизии 
                
//                 break; 

//             case KEY_LEFT:
//                 MoveLeft(game, figure);
//                 break;
//             case ' ':
//                RotateFigure(game, figure, figure->temp_matrix);
//         }
//         if(state == Collision){
//             SetMatrixToZero(figure->current_figure, FIGURE_ROWS,FIGURE_COLS);           
//             ClearLines(game->field); 
//             GenerateNewFigure(figure);
//             UpdateCurrentFigure(figure);
//             state = Moving;
//             //clock_gettime(CLOCK_MONOTONIC, &last_tick);
//         }
//         PrintGameFieldFront(game, game_win);
//         wrefresh(game_win); 
//     }

    


//     return 0;
// } 



