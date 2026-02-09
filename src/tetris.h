#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define GAME_WIN_HEIGHT FIELD_HEIGHT + FRAME_LINE * 2 // ЧЕК ЗНАЧЕНИЯ 
#define GAME_WIN_WIDTH CELL_SIZE * FIELD_WIDTH + FRAME_LINE * 2  // ЧЕК ЗНАЧЕНИЯ 
#define FRAME_LINE 1 
#define CELL_SIZE 3
#define FIGURE_ROWS 4
#define FIGURE_COLS 4
#define MAX_NUM_FIGURES 7
#include "./backend.h"


void PrintGameFieldFront(GameInfo_t *game, WINDOW* game_win);



WINDOW* InitGameFieldFront();



// typedef struct {
//   int** current_figure;
//   int x;
//   int y;
// } FigureInfo_t;
 




// void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

void RenderUserInterface(); 

void InitState();

// void InitState(){
//   GameInfo_t game_info->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH); // для фронта нужна отдельная матрица
//   game_info->score = 0; 
//   //game_info->high_score = 0;
//   game_info->level = 0; 
//   game_info->speed = 0;
// }