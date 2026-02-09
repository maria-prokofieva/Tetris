#include <ncurses.h>

int main(){
    initscr();
    //делать ли проверку на инициализацию?
    // cbreak();
    // noecho();
    // keypad(stdscr, TRUE);
    curs_set(0); // делает курсор невидимым в терминале
    
    // clear();
    
    // Рисуем рамку вокруг всего экрана
    box(stdscr, 0, 0);
    
    // Подсказка в центре экрана
    int height, width;
    getmaxyx(stdscr, height, width);
    // mvprintw(height/2, (width-40)/2, 
            //  "tap any");
    
    // refresh();
    getch();
    endwin();
    return 0;
}

// void render_game_win(){
//     WINDOW* game_win = newwin()
//     box(game_win, 0, 0);
// }