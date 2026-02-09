#include "tetris.h"


int main (){
    initscr();
    keypad(stdscr, TRUE);
    noecho(); 
    curs_set(0); 
    nodelay(stdscr, TRUE);   
    WINDOW* game_win = InitGameFieldFront();

   
    GameInfo_t* game = GetGameInfo();
    InitGameInfo(game);
    GenerateNewFigure(game->figure, game);

   
    int key = 0;
    struct timespec last_tick = {0}; // вынести в отдельную структуру?
    struct timespec now = {0}; // вынести в отдельную структуру?
    long time_interval =  0;
    clock_gettime(CLOCK_MONOTONIC, &last_tick);
    while(game->state != GameOver){
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        int tick_time = 500; 
        time_interval = (now.tv_nsec - last_tick.tv_nsec) / 1000000 + (now.tv_sec - last_tick.tv_sec) * 1000;
        if(time_interval >= tick_time){
            MoveDown(game);
            last_tick = now;
        }
        key = getch();
        switch(key){
            case KEY_RIGHT:
                MoveRight(game);
                break; 

            case KEY_LEFT:
                MoveLeft(game);
                break;
            case ' ':
               IsRotates(game, game->figure->temp_matrix);
        }
        if(game->state == Collision){
            //write(0, 'sss\n', 4);
            // check filled lines
            if (!game->figure || !game->figure->current_figure) {
                 endwin();
                printf("FIGURE POINTER IS NULL before SetMatrixToZero\n");
                exit(0);
            }
            SetMatrixToZero(game->figure->current_figure, FIGURE_ROWS,FIGURE_COLS);
            
            ClearLines(game->field); 
            GenerateNewFigure(game->figure, game);
            game->state = Moving;
            UpdateCurrentFigure(game->figure);
        }
        PrintGameFieldFront(game, game_win);
        wrefresh(game_win); 
    }

    
    endwin();

    return 0;
} 