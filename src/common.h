#include <ncurses.h>
#include <string.h>   

#ifndef COMMON_H
#define COMMON_H

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define GAME_WIN_HEIGHT (FIELD_HEIGHT + FRAME_LINE * 2) 
#define GAME_WIN_WIDTH (CELL_SIZE * FIELD_WIDTH + FRAME_LINE * 2)  
#define FRAME_LINE 1 
#define CELL_SIZE 3
#define FIGURE_ROWS 4
#define FIGURE_COLS 4

#define MID_HEIGHT (GAME_WIN_HEIGHT / 2)
#define SCORE_HEIGHT (MID_HEIGHT - 7)
#define LEVEL_HEIGHT (MID_HEIGHT - 6)
#define HIGH_SCORE_HEIGHT (MID_HEIGHT - 5)
#define NEXT_FIGURE_HEIGHT_TEXT (MID_HEIGHT - 4)
#define MOVE_HEIGHT (MID_HEIGHT + 2)
#define BUTTONS_TEXT_HEIGHT (MID_HEIGHT + 3)
#define GAME_OVER_HEIGHT (MID_HEIGHT - 2)
#define RETRY_HEIGHT (MID_HEIGHT + 1)
#define GAME_NAME_HEIGHT (MID_HEIGHT - 4)

#define CENTER_X_LEFT(text) ((GAME_WIN_WIDTH / 2) - strlen(text)) 
#define CENTER_X(text) (GAME_WIN_WIDTH - strlen(text)) / 2

#define OPTS_NUM 5
#define HUD_NUM 3
#define BUTTONS_TEXT_NUM 2
#define GAME_OVER_TEXT_NUM 2
#define RETRY_TEXT_NUM 1
#define GAME_NAME_NUM 1
#define NEXT_FIG_NUM 1

#define LEFT_INDENT 4

#define START_X 0
#define START_Y 0

#define NEXT_FIGURE_WIDTH  (FIGURE_COLS * CELL_SIZE)
#define NEXT_FIGURE_HEIGHT FIGURE_ROWS
#define NEXT_FIGURE_START_X ((GAME_WIN_WIDTH - NEXT_FIGURE_WIDTH) / 2)
#define NEXT_FIGURE_START_Y ((GAME_WIN_HEIGHT - NEXT_FIGURE_HEIGHT) / 2)

#define ENTER_KEY 10
#define KEY_PAUSE_LOWER 112
#define KEY_PAUSE_UPPER 80
#define KEY_QUIT_UPPER 81
#define KEY_QUIT_LOWER 113
#define KEY_SPACE 32


#include <stdbool.h>
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct 
{
  const char* menu_options[OPTS_NUM];
  const char* hud_params[HUD_NUM];
  const char* buttons_text[BUTTONS_TEXT_NUM];
  const char* game_over_text[GAME_OVER_TEXT_NUM];
  const char* retry_text[RETRY_TEXT_NUM];
  const char* game_name[GAME_NAME_NUM];
  const char* next_fig_text[NEXT_FIG_NUM];
} UiTexts_t;

 typedef enum{
    StartPause,
    Unpaused,
    Paused, 
    GameOverPause,
    QuitGamePause
 } PauseState_t;


GameInfo_t updateCurrentState();
void userInput(UserAction_t action, bool hold);

void EndGame();

void PlayTetris();

WINDOW* InitWindow(int y, int x);
void InitNcurses();
void InitColor();
void InitUiTexts(UiTexts_t* texts);

void PrintFigure(int **figure, int rows, int cols, WINDOW *win, int offset_y, int offset_x);
void PrintStatsFront(GameInfo_t game, WINDOW* state_win, UiTexts_t* texts);
void PrintGameOver(GameInfo_t game, WINDOW* state_win, UiTexts_t* texts);
void PrintStart(WINDOW* game_win, UiTexts_t* texts);
int GetStatByIndex(GameInfo_t game, int i);


#endif