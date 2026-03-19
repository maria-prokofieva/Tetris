#include "common.h"
#include <ncurses.h>
#include "backend.h"

WINDOW* InitGameFieldFront(){
    WINDOW *win = newwin(GAME_WIN_HEIGHT, GAME_WIN_WIDTH, 0, 0);
    box(win, 0, 0);
    refresh();
    return win;
}

WINDOW* InitStateFieldFront(){
    WINDOW *win = newwin(GAME_WIN_HEIGHT, GAME_WIN_WIDTH, 0, GAME_WIN_WIDTH + 2);
    box(win, 0, 0);
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
            if(game.field[i][j] > 0) {
                wattron(game_win, COLOR_PAIR(game.field[i][j]));
                mvwprintw(game_win, height, width, "[ ]"); 
                wattroff(game_win, COLOR_PAIR(game.field[i][j]));      
            } else {
                mvwprintw(game_win, height, width, "   ");          
            }                        
        }
    }  
    wrefresh(game_win);
}

void PrintNextFigure(GameInfo_t game, WINDOW* state_win){ 
    for(int i = 0; i < FIGURE_ROWS; i++) {
        for(int j = 0; j < FIGURE_COLS; j++) {
            int width = (j * CELL_SIZE + FRAME_LINE + GAME_WIN_WIDTH / 2) - 12;
            int height = (i + FRAME_LINE + GAME_WIN_HEIGHT / 2) - 3;   
            if(game.next[i][j] > 0) {
                wattron(state_win, COLOR_PAIR(game.next[i][j]));
                mvwprintw(state_win, height, width, "[ ]");   
                wattroff(state_win, COLOR_PAIR(game.next[i][j]));        
            } else {
                mvwprintw(state_win, height, width, "   ");          
            }                        
        }
    }  
    wrefresh(state_win);
}

void PrintStatsFront(GameInfo_t game, WINDOW* state_win){
    char* text = "Score:";
    char* text_2 = "Level:";
    char* text_3 = "High score:";
    char* text_4 = "Next:";
    char* text_5 = "<  >  -  move";
    char* text_6 = "v     -  drop";
    char* text_7 = "space -  rotate";
    char* text_8 = "p     -  pause";
    char* text_9 = "q     -  exit";


    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 7, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s %d", text, game.score); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 6, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s %d", text_2, game.level); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 5, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s %d", text_3, game.high_score); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 4, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s", text_4); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 + 2, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s", text_5); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 + 3, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s", text_6); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 + 4, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s", text_7); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 + 5, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s", text_8); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 + 6, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s", text_9); 




    wrefresh(state_win);
}

void PrintGameOver(GameInfo_t game, WINDOW* state_win){
    char* text = "Score:";
    char* text_2 = "Level:";
    char* text_3 = "High score:";
    char* text_4 = "GAME OVER";
    char* text_ = "*********";

    char* text_5 = "Try again?";
    char* text_6 = "Press Enter to restart";
    char* text_7 = "Press Q to quit";
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 7, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s %d", text, game.score); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 6, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s %d", text_2, game.level); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 5, (GAME_WIN_WIDTH / 2) - (strlen(text_3)), "%s %d", text_3, game.high_score); 
    wattron(state_win, COLOR_PAIR(4));

    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 2, (GAME_WIN_WIDTH - strlen(text_4)) / 2, "%s", text_4); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 - 1, (GAME_WIN_WIDTH - strlen(text_4)) / 2, "%s", text_); 

    wattroff(state_win, COLOR_PAIR(4));  
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 + 1, (GAME_WIN_WIDTH - strlen(text_5)) / 2, "%s", text_5); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 + 3, (GAME_WIN_WIDTH - strlen(text_6)) / 2, "%s", text_6); 
    mvwprintw(state_win, GAME_WIN_HEIGHT / 2 + 4, (GAME_WIN_WIDTH - strlen(text_7)) / 2, "%s", text_7); 
    wrefresh(state_win);
}

void PrintStart(WINDOW* game_win){
    char* text = "TETRIS";
    char* text_2 = "Press Enter to start";
    char* text_3 = "Press Q to quit";
    wattron(game_win, COLOR_PAIR(7));
    mvwprintw(game_win, GAME_WIN_HEIGHT / 2 - 4, (GAME_WIN_WIDTH / 2) - (strlen(text)/2), "%s", text); 
    wattroff(game_win, COLOR_PAIR(7));  
    mvwprintw(game_win, GAME_WIN_HEIGHT / 2 - 2, (GAME_WIN_WIDTH / 2) - (strlen(text_2)/2), "%s", text_2);  
    mvwprintw(game_win, GAME_WIN_HEIGHT / 2 + 6, (GAME_WIN_WIDTH / 2) - (strlen(text_3)/2), "%s", text_3);  
    wrefresh(game_win);
}


void PlayTetris(){
    WINDOW* game_win = InitGameFieldFront();
    WINDOW* state_win = InitStateFieldFront();
    // nodelay(stdscr, FALSE);
    GameInfo_t game = updateCurrentState();
    bool hold = 0;
    nodelay(stdscr, TRUE);
    while(game.pause != QuitGamePause){
        int key = getch();
            switch(key){
                case KEY_QUIT_UPPER:
                case KEY_QUIT_LOWER:
                    userInput(Terminate, hold);
                    endwin(); 
                    break; 

                case 10:
                case KEY_ENTER: 
                    // обнуление параметров добавить поля фигуры
                    userInput(Start, hold);
                    werase(state_win);
                    box(state_win, 0, 0);

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
        
            game = updateCurrentState(); 
            if(game.pause == StartPause){
                PrintStart(game_win);
            } else if(game.pause == GameOverPause){ 
                werase(state_win);
                box(state_win, 0, 0);
                PrintGameOver(game, state_win);
            } else if(game.pause == Unpaused || game.pause == Paused){
                PrintGameFieldFront(game, game_win);
                PrintNextFigure(game, state_win); 
                PrintStatsFront(game, state_win);  
            }
        
        
        
    }
    EndGame();
    

       
}
    
  







//     //nodelay(stdscr, TRUE);
//     int action = -1;
//     bool hold = 0;
//     key = getch();
//     if((key == 10 || key == KEY_QUIT_LOWER || key == KEY_QUIT_UPPER)){
//         while(game.pause != GameOverPause){
//     switch(key){
//         case KEY_QUIT_UPPER:
//         case KEY_QUIT_LOWER:
//             userInput(Terminate, hold);
//         break;

//         case KEY_ENTER: 
//             userInput(Start, hold);
//                     break;

//                 case KEY_RIGHT:
//                     userInput(Right, hold);

//                     break; 

//                 case KEY_LEFT:
//                     userInput(Left, hold);
//                     break;

//                 case KEY_DOWN:
//                     userInput(Down, hold);
//                     break;

//                 case KEY_SPACE:
//                     userInput(Action, hold);
//                     break;

//                 case KEY_PAUSE_UPPER:
//                 case KEY_PAUSE_LOWER:
//                     userInput(Pause, hold);
//                 break;
                
//                 }    
//             PrintGameFieldFront(game, game_win);
//             PrintNextFigure(game, state_win); 
//             PrintStatsFront(game, state_win);        
//         }

//         userInput(Pause, 0);
//         PrintGameOver(game, state_win);   
//     }
// }


int main() {


    InitNcurses();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    if (can_change_color()) {
        init_color(8, 1000, 500, 0);   // RGB ~ оранжевый
        init_pair(5, 8, COLOR_BLACK);
    }
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK); 
    PlayTetris();
    return 0;
}





