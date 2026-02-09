#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define GAME_WIN_HEIGHT FIELD_HEIGHT + FRAME_LINE * 2 // ЧЕК ЗНАЧЕНИЯ 
#define GAME_WIN_WIDTH CELL_SIZE * FIELD_WIDTH + FRAME_LINE * 2  // ЧЕК ЗНАЧЕНИЯ 
#define FRAME_LINE 1 
#define CELL_SIZE 3
#define FIGURE_ROWS 4
#define FIGURE_COLS 4
#define MAX_NUM_FIGURES 7
#define LIMIT_Y 20 
#define LIMIT_X 10 
#define EMPTY_CELL 0
#define FILLED_CELL 1
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>


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

typedef struct { // ИНФО ТЕКУЩАЯ ФИГУРА 
  int** current_figure;
  int x;
  int y;
  int** temp_matrix;
  Figures_t current_type;
} FigureInfo_t;

typedef enum{ // СОСТОЯНИЯ ИГРЫ
    Initial,
    Spawn,
    Moving, 
    Rotating,
    Clearing, 
    Collision,
    GameOver
}GameState_t;

typedef struct { // ОБЩАЯ ИНФОРМАЦИЯ ПО ИГРЕ
  int **field; // игровое поле
  int **next; // следующая фигура 
  int score; // Текущий счёт
  int high_score; //рекорд
  int level; // Текущий уровень
  int speed; // Скорость игры
  int pause; // флаг паузы
  GameState_t* state; 
  FigureInfo_t *figure;
} GameInfo_t;







typedef enum { // ДЕЙСТВИЯ ИГРОКА
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up, // не используется здесь
  Down,
  Action
} UserAction_t;

 





// void userInput(UserAction_t action, bool hold);



// typedef struct {
//     GameStatus_t status;     // Текущее состояние игры
//     GameInfo_t info;         // Информация об игре
//     FigureInfo_t current;    // Текущая фигура
//     Figures_t next_figure;   // Следующая фигура (тип)
// } MainGameState_t; 



// void InitGame(GameInfo_t* game_parameters){
//     game_parameters->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
// }


GameInfo_t* GetGameInfo();
void InitGameInfo(GameInfo_t* game);

void InitFigure(FigureInfo_t* figure);
void GenerateNewFigure(FigureInfo_t* figure, GameInfo_t* game);
void GenerateTetromino(int random_num, FigureInfo_t* figure);
void GenerateHero(int** current_figure);
void GenerateSmashboy(int** current_figure);

int MoveDown(GameInfo_t *game);
void AddFigureToField(GameInfo_t* game, int** matrix);
void ClearFigureFromGameField(GameInfo_t *game, int** matrix);
int CheckCollision(GameInfo_t* game, int** matrix);
void MoveRight(GameInfo_t* game);
void MoveLeft(GameInfo_t* game);
int CheckRightSide(GameInfo_t* game);
int CheckLeftSide(GameInfo_t* game);

void UpdateCurrentFigure(FigureInfo_t* figure);


void CopyLine(int **field, int row_num);
void MoveLinesDown(int **field, int row_num);
void ClearLines(int **field);
int IsFilledLine(int **field, int row_num);


void GenerateCleveland(int** current_figure);
void SetMatrixToZero(int** matrix, int rows, int cols);
void PrintField(GameInfo_t* game);
void GenerateSmashboy(int** current_figure);
int CheckLeftCollision(FigureInfo_t* figure, GameInfo_t* game);




int IsRotates(GameInfo_t* game, int** matrix);