#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define GAME_WIN_HEIGHT (FIELD_HEIGHT + FRAME_LINE * 2) // ЧЕК ЗНАЧЕНИЯ 
#define GAME_WIN_WIDTH (CELL_SIZE * FIELD_WIDTH + FRAME_LINE * 2)  // ЧЕК ЗНАЧЕНИЯ 
#define FRAME_LINE 1 
#define CELL_SIZE 3
#define FIGURE_ROWS 4
#define FIGURE_COLS 4
#define MAX_NUM_FIGURES 7
#define LIMIT_Y 20 
#define LIMIT_X 10 
#define EMPTY_CELL 0
#define FILLED_CELL 1
#define KEY_ENTER 10
#define KEY_PAUSE_LOWER 112
#define KEY_PAUSE_UPPER 80
#define KEY_QUIT_UPPER 81
#define KEY_QUIT_LOWER 113
#define KEY_SPACE 32
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include "common.h"


// #define PAUSE 'p'
typedef enum{
    Hero, //I
    Smashboy, //O
    RhodeIsland, //S
    Cleveland,//Z 
    OrangeRicky, //L
    BlueRicky, //J
    Teewee //T
}Figures_t; 

typedef enum{
  Degree0,
  Degree90,
  Degree180,
  Degree270
}Rotation_angle;

typedef struct { // ИНФО ТЕКУЩАЯ ФИГУРА 
  int** current_figure;
  int x;
  int y;
  int** temp_matrix;
  Figures_t current_type;
  Figures_t next_type;
  Rotation_angle angle;
}FigureInfo_t;

typedef enum{ // СОСТОЯНИЯ ИГРЫ
    Waiting,
    Initial,
    Spawn,
    Moving, 
    Rotating,
    Clearing, 
    Collision,
    GameOver
}GameState_t;


 typedef enum {
    MoveDownOk,
    MoveDownCollision
 } MoveResult_t;

 typedef enum{
    Unpaused,
    Paused, 
    GameOverPause
 } PauseState_t;

// typedef struct {
//   struct timespec last_tick;
//   struct timespec now;
//   long time_interval;
//   int tick_time;
// } Timer_t;

typedef struct {
  GameInfo_t* game;
  GameState_t current_state;
  FigureInfo_t* figure;
} MainGameState_t;






// void userInput(UserAction_t action, bool hold);



// typedef struct {
//     GameStatus_t status;     // Текущее состояние игры
//     GameInfo_t info;         // Информация об игре
//     FigureInfo_t current;    // Текущая фигура
//     Figures_t next_figure;   // Следующая фигура (тип)
// } MainGameState_t; 



GameInfo_t* GetGameInfo();
void InitGameInfoIfNeed(MainGameState_t* game_state); 
void InitFigureIfNeed(MainGameState_t* game_state);
//GameState_t* Initstate();
void GenerateNewFigure(MainGameState_t *game_state);
void GenerateTetromino(int random_num, int** figure);
void GenerateHero(int** current_figure);
void GenerateSmashboy(int** current_figure);
int MoveDown(GameInfo_t *game, FigureInfo_t* figure);
void AddFigureToField(GameInfo_t* game, int** matrix, FigureInfo_t* figure);
void ClearFigureFromGameField(GameInfo_t *game, FigureInfo_t *figure);
int CheckCollision(GameInfo_t* game, int** matrix, int y, int x);
void MoveRight(GameInfo_t* game, FigureInfo_t* figure);
void MoveLeft(GameInfo_t* game, FigureInfo_t* figure);
int CheckRightSide(GameInfo_t* game, FigureInfo_t* figure);
int CheckLeftSide(GameInfo_t* game, FigureInfo_t* figure);

void UpdateCurrentFigure(FigureInfo_t* figure);


void CopyLine(int **field, int row_num);
void MoveLinesDown(int **field, int row_num);
int ClearLines(int **field);
int IsFilledLine(int **field, int row_num);


void GenerateCleveland(int** current_figure);
void SetMatrixToZero(int** matrix, int rows, int cols);
void PrintField(GameInfo_t* game);
void GenerateSmashboy(int** current_figure);
int CheckLeftCollision(FigureInfo_t* figure, GameInfo_t* game);

void TetrisFsm(MainGameState_t *game_state);


void RotateFigure(GameInfo_t* game, FigureInfo_t* figure);
void RotateHero(GameInfo_t* game, FigureInfo_t* figure);
void RotateAnotherFigures(GameInfo_t* game, FigureInfo_t* figure);


