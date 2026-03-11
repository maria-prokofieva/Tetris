#include "common.h"
#include <ncurses.h>
#include "backend.h"

WINDOW* InitGameFieldFront(){
    WINDOW *win = newwin(GAME_WIN_HEIGHT, GAME_WIN_WIDTH, 0, 0);
    box(win, 0, 0);
    //char* text = "Tetris";
    //mvwprintw(win, GAME_WIN_HEIGHT / 2 - 2, (GAME_WIN_WIDTH / 2) - (strlen(text)/2), "%s", text); 
    refresh();
    return win;
}

WINDOW* InitStateFieldFront(){
    WINDOW *win = newwin(GAME_WIN_HEIGHT, GAME_WIN_WIDTH, 0, GAME_WIN_WIDTH + 2);
    box(win, 0, 0);
    //char* text = "Tetris";
    //mvwprintw(win, GAME_WIN_HEIGHT / 2 - 2, (GAME_WIN_WIDTH / 2) - (strlen(text)/2), "%s", text); 
    wrefresh(win);
    return win;
}

void InitNcurses() {
    initscr();
    keypad(stdscr, TRUE);
    noecho(); 
    curs_set(0); 
   // nodelay(stdscr, TRUE);   
}

void PrintGameFieldFront(GameInfo_t game, WINDOW* game_win){ 
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

void PrintStateFieldFront(GameInfo_t game, WINDOW* state_win){ 
    for(int i = 0; i < FIGURE_ROWS; i++) {
        for(int j = 0; j < FIGURE_COLS; j++) {
            int width = (j * CELL_SIZE + FRAME_LINE + GAME_WIN_WIDTH / 2) - 2;
            int height = i + FRAME_LINE + GAME_WIN_HEIGHT / 2;   
            if(game.next[i][j] == 1) {
                mvwprintw(state_win, height, width, "[ ]");         
            } else {
                mvwprintw(state_win, height, width, "   ");          
            }                        
        }
    }  
    wrefresh(state_win);
}

void PrintStatesFront(GameInfo_t game, WINDOW* state_win){
    char* text = "Score:";
    char* text_2 = "Level:";

    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 2, (GAME_WIN_WIDTH / 2) - (strlen(text)/2), "%s %d", text, game.score); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 1, (GAME_WIN_WIDTH / 2) - (strlen(text)/2), "%s %d", text_2, game.level); 

}


void PlayTetris(){
    WINDOW* game_win = InitGameFieldFront();
    WINDOW* state_win = InitStateFieldFront();
    int tick = 0;
    int n = 0;  
    GameInfo_t game = updateCurrentState();
    //wrefresh(game_win); 
    //int height = GAME_WIN_HEIGHT / 2;
    char* text = "Tetris";
    char* text_2 = "Press Enter to start";
    mvwprintw(game_win, GAME_WIN_HEIGHT / 2 - 2, (GAME_WIN_WIDTH / 2) - (strlen(text)/2), "%s", text); 
    mvwprintw(game_win, GAME_WIN_HEIGHT / 2 - 1, (GAME_WIN_WIDTH / 2) - (strlen(text_2)/2), "%s", text_2);  
    //ГАСНЕТ ЕСЛИ НАЖАЛИ НЕ ЕНТЕР
    wrefresh(game_win);
    nodelay(stdscr, FALSE);   
    while(game.pause != GameOverPause){
    int key = getch();
    nodelay(stdscr, TRUE);
    int action = -1;
    bool hold = 0;
    switch(key){
            case KEY_QUIT_UPPER:
            case KEY_QUIT_LOWER:
                userInput(Terminate, hold);
            break;

            case KEY_ENTER: 
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

            case KEY_SPACE:
                userInput(Action, hold);
                break;

            case KEY_PAUSE_UPPER:
            case KEY_PAUSE_LOWER:
                userInput(Pause, hold);
            break;
            
        }    
        if (tick >= 20) {         
           game = updateCurrentState();
           PrintGameFieldFront(game, game_win);
           PrintStateFieldFront(game, state_win); 
           PrintStatesFront(game, state_win);
            tick = 0;
        }
        napms(20); 
        tick++;
    }
    EndGame();
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



