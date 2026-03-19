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
//#define KEY_ENTER 10
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
    Hero, // I
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
    GameOver,
    GameEnd
}GameState_t;


 typedef enum {
    MoveDownOk,
    MoveDownCollision
 } MoveResult_t;

 typedef enum{
    StartPause,
    Unpaused,
    Paused, 
    GameOverPause,
    QuitGamePause
 } PauseState_t;

typedef struct {
  struct timespec start;
  struct timespec now;
} Timer_t;

typedef struct {
  GameInfo_t* game;
  GameState_t current_state;
  FigureInfo_t* figure;
  Timer_t* time;
} MainGameState_t;


MainGameState_t* GetMainGameInfo();
int GetRecord();
void SetRecord(int score);
void UserMoveDown(MainGameState_t* game_state);
void userInput(UserAction_t action, bool hold);
void PauseGame(MainGameState_t* game_state);
void InitRandom();
GameInfo_t updateCurrentState();
int GenerateRandomNum(int max_num);
int** InitMatrix(int rows, int cols);
void UpdateCurrentFigure(FigureInfo_t* figure);
void InitInfoIfNeed(MainGameState_t* game_state);
void InitFigureIfNeed(MainGameState_t* game_state);
void CopyStaticMatrixToDynamic(int rows, int cols, int **matrix, int(*copied_matrix)[cols]);

void GenerateSmashboy(int** current_figure);
void GenerateRhodeIsland(int** current_figure);
void GenerateHero(int** current_figure);
void GenerateOrangeRicky(int** current_figure);
void GenerateCleveland(int** current_figure);
void GenerateTeewee(int** current_figure);
void GenerateBlueRicky(int** current_figure);
void GenerateTetromino(int random_num, int** figure);
void GenerateNewFigure(MainGameState_t *game_state);
void EquateMatrices(int** current_figure, int** next);

void ClearFigureFromGameField(GameInfo_t *game, FigureInfo_t *figure);
void AddFigureToField(GameInfo_t* game, int** matrix, FigureInfo_t* figure);
int MoveDown(GameInfo_t *game, FigureInfo_t* figure);
int MoveDownToTheEnd(GameInfo_t *game, FigureInfo_t* figure);
int CheckCollision(GameInfo_t* game, int** matrix, int y, int x);
int IsFilledLine(int** field, int row_num);
void MoveLeft(GameInfo_t* game, FigureInfo_t* figure);
void MoveRight(GameInfo_t* game, FigureInfo_t* figure);
long int GetTimeDiff(MainGameState_t *game_state);
void SpawnFigure(MainGameState_t *game_state);

void SetMatrixToZero(int** matrix, int rows, int cols);

int ClearLines(int** field);
void MoveLinesDown(int** field, int row_num);
void RotateFigure(GameInfo_t* game, FigureInfo_t* figure);
void RotateHero(GameInfo_t* game, FigureInfo_t* figure);
void RotateAnotherFigures(GameInfo_t* game, FigureInfo_t* figure);
void SpawnFigure(MainGameState_t *game_state);
void TetrisFsm(MainGameState_t *game_state);
void CountStats(int num_filled_lines, MainGameState_t *game_state);
void FreeMatrix(int** matrix, int row);
void TerminateGame(MainGameState_t* game_state);
void ResetParams(MainGameState_t* game_state);
void EndGame();