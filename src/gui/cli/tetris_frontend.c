#include "common.h"

WINDOW* InitWindow(int y, int x){
    WINDOW *win = newwin(GAME_WIN_HEIGHT, GAME_WIN_WIDTH, y, x);
    box(win, 0, 0);
    wrefresh(win);
    return win;
}

void InitNcurses() {
    initscr();
    keypad(stdscr, TRUE);
    noecho(); 
    curs_set(0); 
    nodelay(stdscr, TRUE);   
}


void PrintFigure(int **figure, int rows, int cols, WINDOW *win, int offset_y, int offset_x) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int height = i + offset_y;
            int width  = j * CELL_SIZE + offset_x;
            if (figure[i][j] > 0) {
                wattron(win, COLOR_PAIR(figure[i][j]));
                mvwprintw(win, height, width, "[ ]");
                wattroff(win, COLOR_PAIR(figure[i][j]));
            } else {
                mvwprintw(win, height, width, "   ");
            }
        }
    }
    wrefresh(win);
}


void InitUiTexts(UiTexts_t* texts){
    texts->menu_options[0] = "<   > -  move";
    texts->menu_options[1] = "  v   -  drop";
    texts->menu_options[2] = "space -  rotate";
    texts->menu_options[3] = "  p   -  pause";
    texts->menu_options[4] = "  q   -  exit";

    texts->hud_params[0] = "Score:";
    texts->hud_params[1] = "Level:";
    texts->hud_params[2] = "High score:";

    texts->buttons_text[0] = "Press Enter to start";
    texts->buttons_text[1] = "Press Q to quit";

    texts->game_over_text[0] = "GAME OVER"; 
    texts->game_over_text[1] = "*********";

    texts->game_name[0] = "TETRIS";

    texts->retry_text[0] = "Try again?";

    texts->next_fig_text[0] = "Next:";
}


void PrintStatsFront(GameInfo_t game, WINDOW* state_win, UiTexts_t* texts){
    for(int i = 0; i < HUD_NUM; i++){
        mvwprintw(state_win, SCORE_HEIGHT + i, LEFT_INDENT, "%s %d", texts->hud_params[i], GetStatByIndex(game, i));
    }

    mvwprintw(state_win, NEXT_FIGURE_HEIGHT_TEXT, LEFT_INDENT, "%s", texts->next_fig_text[0]);

    for(int i = 0; i < OPTS_NUM; i++){
        mvwprintw(state_win, MOVE_HEIGHT + i, LEFT_INDENT, "%s", texts->menu_options[i]);
    }
    wrefresh(state_win);
}

int GetStatByIndex(GameInfo_t game, int i){
    int res = -1;
    switch(i){
        case 0: 
            res = game.score;
            break;

        case 1: 
            res = game.level;
            break;

        case 2: 
            res = game.high_score;
            break;

        default: 
            break;
    }
    return res;
}

void PrintGameOver(GameInfo_t game, WINDOW* state_win, UiTexts_t* texts){
    for(int i = 0; i < HUD_NUM; i++){
        mvwprintw(state_win, SCORE_HEIGHT + i, LEFT_INDENT, "%s %d", texts->hud_params[i],  GetStatByIndex(game, i));
    }

    wattron(state_win, COLOR_PAIR(4));
    for(int i = 0; i < GAME_OVER_TEXT_NUM; i++){
        mvwprintw(state_win, GAME_OVER_HEIGHT + i, CENTER_X(texts->game_over_text[0]), "%s", texts->game_over_text[i]);     
    }
    wattroff(state_win, COLOR_PAIR(4));  

    mvwprintw(state_win, RETRY_HEIGHT, CENTER_X(texts->retry_text[0]), "%s", texts->retry_text[0]); 

    for(int i = 0; i < BUTTONS_TEXT_NUM; i++){
        mvwprintw(state_win, BUTTONS_TEXT_HEIGHT + i, CENTER_X(texts->buttons_text[i]), "%s", texts->buttons_text[i]); 
    }
    wrefresh(state_win);
}

void PrintStart(WINDOW* game_win, UiTexts_t* texts){

    wattron(game_win, COLOR_PAIR(7));
    mvwprintw(game_win, GAME_NAME_HEIGHT, CENTER_X(texts->game_name[0]), "%s", texts->game_name[0]); 
    wattroff(game_win, COLOR_PAIR(7));  

    for(int i = 0; i < BUTTONS_TEXT_NUM; i++){
        mvwprintw(game_win, BUTTONS_TEXT_HEIGHT + i, CENTER_X(texts->buttons_text[i]), "%s", texts->buttons_text[i]); 
    } 
    wrefresh(game_win);
}

void InitColor(){
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK); 
    init_color(8, 1000, 500, 0);   
    init_pair(5, 8, COLOR_BLACK);
}


void PlayTetris(){

    UiTexts_t texts;
    InitUiTexts(&texts);
    WINDOW* game_win = InitWindow(START_X, START_Y);
    WINDOW* state_win = InitWindow(START_X, GAME_WIN_WIDTH + 2);
    GameInfo_t game = updateCurrentState();
    bool hold = 0;
    while(game.pause != QuitGamePause){
        int key = getch();
            switch(key){
                case KEY_QUIT_UPPER:
                case KEY_QUIT_LOWER:
                    userInput(Terminate, hold);
                    endwin(); 
                    break; 

                case ENTER_KEY:
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
            werase(game_win);
            box(game_win, 0, 0);
            PrintStart(game_win, &texts);
        } else if(game.pause == GameOverPause){ 
            werase(state_win);
            box(state_win, 0, 0);
            PrintGameOver(game, state_win, &texts);
        } else if(game.pause == Unpaused || game.pause == Paused){
            PrintFigure(game.field, FIELD_HEIGHT, FIELD_WIDTH, game_win, FRAME_LINE, FRAME_LINE);
            PrintFigure(game.next, FIGURE_ROWS, FIGURE_COLS, state_win, NEXT_FIGURE_START_Y , NEXT_FIGURE_START_X);
            PrintStatsFront(game, state_win, &texts);  
        }      
    }
    EndGame();       
}