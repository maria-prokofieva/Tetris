#include <check.h>
#include <stdio.h>
#include "backend.h"


START_TEST(test_init_matrix)
{
    int rows = 2;
    int cols = 3;
    int **matrix = InitMatrix(rows, cols);
    ck_assert_ptr_nonnull(matrix);
    for(int i = 0; i < rows; i++){
        ck_assert_ptr_nonnull(matrix[i]);
        for(int j = 0; j < cols; j++){
            ck_assert_int_eq(matrix[i][j], 0);
        }
    }
    FreeMatrix(matrix, rows);
}
END_TEST

START_TEST(test_free_matrix_null)
{
    FreeMatrix(NULL, 5);
    ck_assert(1);
}
END_TEST

START_TEST(test_is_filled_line)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    for(int j = 0; j < FIELD_WIDTH; j++){
        field[5][j] = 1;
    }
    int result = IsFilledLine(field, 5);
    ck_assert_int_eq(result, 1);
    FreeMatrix(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(test_clear_lines)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    for(int j = 0; j < FIELD_WIDTH; j++){
        field[FIELD_HEIGHT - 1][j] = 1;
    }
    int cleared = ClearLines(field);
    ck_assert_int_eq(cleared, 1);
    for(int j = 0; j < FIELD_WIDTH; j++){
        ck_assert_int_eq(field[FIELD_HEIGHT - 1][j], 0);
    }
    FreeMatrix(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(test_generate_random_num)
{
    int max = 7;
    for(int i = 0; i < 30; i++){
        for(int j = 1; j < max + 1; j++){
            int num = GenerateRandomNum(j);
            ck_assert_int_lt(num, max);
            ck_assert_int_ge(num, 0);
        }
    }
}
END_TEST

START_TEST(test_check_no_collision)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    int **figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure[0][0] = 1;
    GameInfo_t game = {0};
    game.field = field;
    int result = CheckCollision(&game, figure, 5, 5);
    ck_assert_int_eq(result, 0);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_check_collision_bottom)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    int **figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure[0][0] = 1;
    GameInfo_t game = {0};
    game.field = field;
    int result = CheckCollision(&game, figure, FIELD_HEIGHT, 5);
    ck_assert_int_eq(result, 1);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_check_collision_left_wall)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    int **figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure[0][0] = 1;
    GameInfo_t game = {0};
    game.field = field;
    int result = CheckCollision(&game, figure, 5, -1);
    ck_assert_int_eq(result, 1);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_check_collision_right_wall)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    int **figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure[0][0] = 1;
    GameInfo_t game = {0};
    game.field = field;
    int result = CheckCollision(&game, figure, 5, FIELD_WIDTH);
    ck_assert_int_eq(result, 1);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_check_collision_block)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    int **figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure[0][0] = 1;
    field[5][5] = 1;
    GameInfo_t game = {0};
    game.field = field;
    int result = CheckCollision(&game, figure, 5, 5);
    ck_assert_int_eq(result, 1);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_check_no_collision_2)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    int **figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure[0][0] = 1;
    field[0][1] = 1;
    GameInfo_t game = {0};
    game.field = field;
    int result = CheckCollision(&game, figure, 0, 0);
    ck_assert_int_eq(result, 0);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_move_down)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    GameInfo_t game = {0};
    game.field = field;
    game.pause = Unpaused;
    FigureInfo_t figure = {0};
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.current_figure[0][0] = 1;
    figure.y = 3;
    figure.x = 3;
    AddFigureToField(&game, figure.current_figure, &figure);
    int status = MoveDown(&game, &figure);
    ck_assert_int_eq(status, MoveDownOk);
    ck_assert_int_eq(figure.y, 4);
    ck_assert_int_eq(figure.x, 3);
    ck_assert_int_eq(field[4][3], 1);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_move_down_collision)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    field[5][3] = 1;
    GameInfo_t game = {0};
    game.field = field;
    game.pause = Unpaused;
    FigureInfo_t figure = {0};
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.current_figure[0][0] = 1;
    figure.y = 4;
    figure.x = 3;
    AddFigureToField(&game, figure.current_figure, &figure);
    int status = MoveDown(&game, &figure);
    ck_assert_int_eq(status, MoveDownCollision);
    ck_assert_int_eq(figure.y, 4);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_add_figure_to_field)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    int **matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    matrix[0][0] = 1;
    GameInfo_t game = {0};
    game.field = field;
    FigureInfo_t figure = {0};
    figure.current_figure = matrix;
    figure.x = 3;
    figure.y = 4;
    AddFigureToField(&game,  figure.current_figure, &figure);
    ck_assert_int_eq(field[4][3], 1);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(matrix, FIGURE_ROWS);
}
END_TEST

START_TEST(test_count_stats)
{
    MainGameState_t state = {0};
    state.game = malloc(sizeof(GameInfo_t));
    state.game->score = 0;
    state.game->level = 1;
    state.game->high_score = 0;
    CountStats(2, &state);
    ck_assert_int_eq(state.game->score, 300);
    free(state.game);
}
END_TEST

START_TEST(test_count_stats_2)
{
    MainGameState_t state = {0};
    state.game = malloc(sizeof(GameInfo_t));
    state.game->score = 0;
    state.game->level = 1;
    state.game->high_score = 0;
    CountStats(3, &state);
    ck_assert_int_eq(state.game->score, 700);
    ck_assert_int_eq(state.game->level, 2);
    free(state.game);
}
END_TEST


START_TEST(test_count_stats_3)
{
    MainGameState_t state = {0};
    state.game = malloc(sizeof(GameInfo_t));
    state.game->score = 0;
    state.game->level = 1;
    state.game->high_score = 0;
    for(int i = 0; i < 10; i++){
        CountStats(4, &state);
    }
    ck_assert_int_eq(state.game->level, 10);
    free(state.game);
}
END_TEST

START_TEST(test_count_stats_4)
{
    MainGameState_t state = {0};
    state.game = malloc(sizeof(GameInfo_t));
    state.game->score = 0;
    state.game->level = 1;
    state.game->high_score = 0;
    CountStats(1, &state);
    ck_assert_int_eq(state.game->level, 1);
    ck_assert_int_eq(state.game->score, 100);
    free(state.game);
}
END_TEST


START_TEST(test_collision_top)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    int **figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure[0][0] = 1;
    GameInfo_t game = {0};
    game.field = field;
    int result = CheckCollision(&game, figure, -1, 5);
    ck_assert_int_eq(result, 1);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_move_right)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    GameInfo_t game = {0};
    game.field = field;
    FigureInfo_t fig = {0};
    fig.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    fig.current_figure[0][0] = 1;
    fig.x = 3;
    fig.y = 3;
    AddFigureToField(&game, fig.current_figure, &fig);
    MoveRight(&game, &fig);
    ck_assert_int_eq(fig.x, 4);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(fig.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_move_left)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    GameInfo_t game = {0};
    game.field = field;
    FigureInfo_t figure = {0};
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.current_figure[0][0] = 1;
    figure.x = 5;
    figure.y = 5;
    AddFigureToField(&game, figure.current_figure, &figure);
    MoveLeft(&game, &figure);
    ck_assert_int_eq(figure.x, 4);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_move_down_pause)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    GameInfo_t game = {0};
    game.field = field;
    game.pause = Paused;
    FigureInfo_t figure = {0};
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.current_figure[0][0] = 1;
    figure.x = 3;
    figure.y = 3;
    int old_y = figure.y;
    MoveDown(&game, &figure);
    ck_assert_int_eq(figure.y, old_y);
    FreeMatrix(field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_rotate_teewee_coordinates)
{
    GameInfo_t game = {0};
    FigureInfo_t figure = {0};
    game.field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.current_type = Teewee;
    figure.angle = Degree0;
    figure.x = 4;
    figure.y = 5;
    GenerateTeewee(figure.current_figure);
    AddFigureToField(&game, figure.current_figure, &figure);
    RotateFigure(&game, &figure);
    ck_assert_int_eq(figure.angle, Degree90);
    ck_assert_int_ne(game.field[5][4], 0);
    ck_assert_int_ne(game.field[6][4], 0);
    ck_assert_int_ne(game.field[7][4], 0);
    ck_assert_int_ne(game.field[6][5], 0);
    ck_assert_int_eq(game.field[5][5], 0);
    ck_assert_int_eq(game.field[5][6], 0);
    FreeMatrix(game.field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
    FreeMatrix(figure.temp_matrix, FIGURE_ROWS);
}
END_TEST

START_TEST(test_clear_lines_down)
{
    int **field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    for(int j = 0; j < FIELD_WIDTH; j++){
        field[FIELD_HEIGHT - 1][j] = 1;
    }
    for(int j = 0; j < FIELD_WIDTH; j++){
        field[FIELD_HEIGHT - 2][j] = 2;
    }
    field[FIELD_HEIGHT - 2][5] = 0;
    int cleared = ClearLines(field);
    ck_assert_int_eq(cleared, 1);
    ck_assert_int_eq(field[FIELD_HEIGHT - 2][5], 0);
    for(int j = 0; j < FIELD_WIDTH; j++){
        if(j != 5){
        ck_assert_int_eq(field[FIELD_HEIGHT - 1][j], 2);
        }
    }
    FreeMatrix(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(test_pause_game_set_pause)
{
    MainGameState_t state = {0};
    GameInfo_t game = {0};
    Timer_t timer = {0};
    state.game = &game;
    state.time = &timer;
    state.game->pause = Unpaused;
    PauseGame(&state);
    ck_assert_int_eq(state.game->pause, Paused);
}
END_TEST

START_TEST(test_pause_game_unpause)
{
    MainGameState_t state = {0};
    GameInfo_t game = {0};
    Timer_t timer = {0};
    state.game = &game;
    state.time = &timer;
    state.game->pause = Paused;
    PauseGame(&state);
    ck_assert_int_eq(state.game->pause, Unpaused);
}
END_TEST

START_TEST(test_rotate_hero)
{
    GameInfo_t game = {0};
    FigureInfo_t figure = {0};
    game.field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.x = 3;
    figure.y = 0;
    figure.angle = Degree0;
    figure.current_type = Hero;
    GenerateHero(figure.current_figure);
    RotateFigure(&game, &figure);
    ck_assert_int_eq(figure.angle, Degree90);
    int expected[FIGURE_ROWS][FIGURE_COLS] = {
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
    };
    for(int i = 0; i < FIGURE_ROWS; i++){
        for(int j = 0; j < FIGURE_COLS; j++){
            ck_assert_int_eq(figure.current_figure[i][j], expected[i][j]);
        }
    }
    FreeMatrix(game.field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
    FreeMatrix(figure.temp_matrix, FIGURE_ROWS);
}
END_TEST

START_TEST(test_user_input_terminate)
{
    updateCurrentState();
    MainGameState_t *state = GetMainGameInfo();
    userInput(Terminate, false);
    ck_assert_ptr_null(state->game);
}
END_TEST

START_TEST(test_user_move_down)
{
    MainGameState_t state = {0};
    GameInfo_t game = {0};
    FigureInfo_t figure = {0};
    state.game = &game;
    state.figure = &figure;
    game.pause = Unpaused;
    game.field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    GenerateSmashboy(figure.current_figure);
    figure.x = 3;
    figure.y = FIELD_HEIGHT - 3;
    figure.current_type = Smashboy;
    state.current_state = Moving;
    UserMoveDown(&state);
    ck_assert_int_eq(state.current_state, Collision);
    FreeMatrix(game.field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_user_input_start)
{
    MainGameState_t *state = GetMainGameInfo();
    state->current_state = Waiting;
    userInput(Start, false);
    ck_assert_int_eq(state->current_state, Initial);
}
END_TEST

START_TEST(test_user_input_right)
{
    MainGameState_t *state = GetMainGameInfo();
    GameInfo_t game = {0};
    FigureInfo_t figure = {0};
    game.field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    GenerateSmashboy(figure.current_figure);
    figure.x = 3;
    figure.y = 5;
    state->game = &game;
    state->figure = &figure;
    state->current_state = Moving;
    state->game->pause = Unpaused;
    int old_x = figure.x;
    userInput(Right, false);
    ck_assert_int_eq(figure.x, old_x + 1);
    FreeMatrix(game.field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_user_input_left)
{
    MainGameState_t *state = GetMainGameInfo();
    GameInfo_t game = {0};
    FigureInfo_t figure = {0};
    game.field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    GenerateSmashboy(figure.current_figure);
    figure.x = 4;
    figure.y = 5;
    state->game = &game;
    state->figure = &figure;
    state->current_state = Moving;
    state->game->pause = Unpaused;
    int old_x = figure.x;
    userInput(Left, false);
    ck_assert_int_eq(figure.x, old_x - 1);
    FreeMatrix(game.field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_fsm_waiting)
{
    MainGameState_t state = {0};
    state.current_state = Waiting;
    TetrisFsm(&state);
    ck_assert_int_eq(state.current_state, Waiting);
}
END_TEST

START_TEST(test_fsm_initial)
{
    updateCurrentState(); 
    MainGameState_t *state = GetMainGameInfo();
    state->current_state = Initial;
    TetrisFsm(state);
    ck_assert_int_eq(state->current_state, Spawn);
}
END_TEST

START_TEST(test_fsm_spawn)
{
    MainGameState_t state = {0};
    GameInfo_t game = {0};
    FigureInfo_t figure = {0};
    game.field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    game.next  = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.next_type = -1;
    state.game = &game;
    state.figure = &figure;
    state.current_state = Spawn;
    TetrisFsm(&state);
    ck_assert_int_eq(state.current_state, Moving);
    FreeMatrix(game.field, FIELD_HEIGHT);
    FreeMatrix(game.next, FIGURE_ROWS);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
}
END_TEST

START_TEST(test_terminate_game)
{
    MainGameState_t state = {0};
    GameInfo_t *game = malloc(sizeof(GameInfo_t));
    FigureInfo_t *figure = malloc(sizeof(FigureInfo_t));
    Timer_t *time = malloc(sizeof(Timer_t));
    game->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    game->next  = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure->current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure->temp_matrix    = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    state.game = game;
    state.figure = figure;
    state.time = time;
    TerminateGame(&state);
    ck_assert_ptr_eq(state.game, NULL);
    ck_assert_ptr_eq(state.figure, NULL);
    ck_assert_ptr_eq(state.time, NULL);
}
END_TEST

START_TEST(test_end_game)
{
    MainGameState_t *state = GetMainGameInfo();
    state->game = malloc(sizeof(GameInfo_t));
    state->figure = malloc(sizeof(FigureInfo_t));
    state->time = malloc(sizeof(Timer_t));
    state->game->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    state->game->next = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    state->figure->current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    state->figure->temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    EndGame();
    ck_assert_ptr_eq(state->game, NULL);
    ck_assert_ptr_eq(state->figure, NULL);
    ck_assert_ptr_eq(state->time, NULL);
}
END_TEST

START_TEST(test_rotate_another_figure)
{
    MainGameState_t state = {0};
    state.game = malloc(sizeof(GameInfo_t));
    state.game->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    state.game->next = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    state.game->pause = Unpaused;
    InitFigureIfNeed(&state);
    GenerateTetromino(Teewee, state.figure->current_figure);
    state.figure->current_type = Teewee;
    UpdateCurrentFigure(state.figure);
    AddFigureToField(state.game, state.figure->current_figure, state.figure);
    int old_angle = state.figure->angle;
    int old_x = state.figure->x;
    int old_y = state.figure->y;
    RotateFigure(state.game, state.figure);
    ck_assert_int_eq(state.figure->angle, old_angle + 1);
    ck_assert_int_ge(state.figure->x, old_x - 1);
    ck_assert_int_le(state.figure->x, old_x + 1);
    ck_assert_int_ge(state.figure->y, old_y - 2);
    ck_assert_int_le(state.figure->y, old_y + 2);
    TerminateGame(&state);
}
END_TEST

START_TEST(test_rotate_smashboy)
{
    GameInfo_t game = {0};
    FigureInfo_t figure = {0};
    game.field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    figure.current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure.current_type = Smashboy;
    figure.x = 3;
    figure.y = 0;
    figure.angle = Degree0;
    GenerateSmashboy(figure.current_figure);
    int old_matrix[FIGURE_ROWS][FIGURE_COLS];
    for (int i = 0; i < FIGURE_ROWS; i++) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            old_matrix[i][j] = figure.current_figure[i][j];
        }
    }
    RotateFigure(&game, &figure);
    for (int i = 0; i < FIGURE_ROWS; i++) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            ck_assert_int_eq(old_matrix[i][j], figure.current_figure[i][j]);
        }
    }
    FreeMatrix(game.field, FIELD_HEIGHT);
    FreeMatrix(figure.current_figure, FIGURE_ROWS);
    FreeMatrix(figure.temp_matrix, FIGURE_ROWS);
}
END_TEST

START_TEST(test_init_info_if_need)
{
    MainGameState_t state = {0};
    InitInfoIfNeed(&state);
    ck_assert_ptr_nonnull(state.game);
    ck_assert_ptr_nonnull(state.game->field);
    ck_assert_ptr_nonnull(state.game->next);
    ck_assert_ptr_nonnull(state.figure);
    ck_assert_ptr_nonnull(state.time);
    ck_assert_int_eq(state.game->pause, StartPause);
    ck_assert_int_eq(state.game->level, 1);
    ck_assert_int_eq(state.game->score, 0);
    ck_assert(state.figure->next_type == -1);
    ck_assert_ptr_nonnull(state.game->field[0]);
    GameInfo_t *old_game = state.game;
    InitInfoIfNeed(&state);
    ck_assert_ptr_eq(state.game, old_game);
    TerminateGame(&state);
}
END_TEST

START_TEST(test_user_input_action)
{
    MainGameState_t *state = GetMainGameInfo();
    state->game = malloc(sizeof(GameInfo_t));
    state->figure = malloc(sizeof(FigureInfo_t));
    state->game->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    state->game->next = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    state->figure->current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    state->figure->temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    state->figure->x = FIELD_WIDTH / 2;
    state->figure->y = 0;
    state->figure->angle = Degree0;
    state->figure->current_type = Teewee;
    GenerateTeewee(state->figure->current_figure);
    state->game->pause = Unpaused;
    state->current_state = Moving;
    userInput(Action, false);
    ck_assert_int_eq(state->current_state, Moving);
    FreeMatrix(state->game->field, FIELD_HEIGHT);
    FreeMatrix(state->game->next, FIGURE_ROWS);
    FreeMatrix(state->figure->current_figure, FIGURE_ROWS);
    FreeMatrix(state->figure->temp_matrix, FIGURE_ROWS);
    free(state->game);
    free(state->figure);
    state->game = NULL;
    state->figure = NULL;
}
END_TEST


Suite *test_suite(void) {
    Suite *s = suite_create("tetris_backend");

    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_generate_random_num);
    tcase_add_test(tc, test_init_matrix);
    tcase_add_test(tc, test_is_filled_line);
    tcase_add_test(tc, test_clear_lines);
    tcase_add_test(tc, test_check_no_collision);
    tcase_add_test(tc, test_check_no_collision_2);
    tcase_add_test(tc, test_check_collision_bottom);
    tcase_add_test(tc, test_check_collision_left_wall);
    tcase_add_test(tc, test_check_collision_right_wall);
    tcase_add_test(tc, test_check_collision_block);
    tcase_add_test(tc, test_collision_top);
    tcase_add_test(tc, test_move_down);
    tcase_add_test(tc, test_move_down_collision);
    tcase_add_test(tc, test_add_figure_to_field);
    tcase_add_test(tc, test_count_stats);
    tcase_add_test(tc, test_move_left);
    tcase_add_test(tc, test_move_right);
    tcase_add_test(tc, test_move_down_pause);
    tcase_add_test(tc, test_free_matrix_null);
    tcase_add_test(tc, test_clear_lines_down);
    tcase_add_test(tc, test_count_stats_2);
    tcase_add_test(tc, test_count_stats_3);
    tcase_add_test(tc, test_count_stats_4);
    tcase_add_test(tc, test_pause_game_set_pause);
    tcase_add_test(tc, test_pause_game_unpause);
    tcase_add_test(tc, test_rotate_hero);
    tcase_add_test(tc, test_user_input_terminate);
    tcase_add_test(tc, test_user_move_down);
    tcase_add_test(tc, test_user_input_start);
    tcase_add_test(tc, test_user_input_right);
    tcase_add_test(tc, test_user_input_left);
    tcase_add_test(tc, test_fsm_waiting);
    tcase_add_test(tc, test_fsm_initial);
    tcase_add_test(tc, test_fsm_spawn);
    tcase_add_test(tc, test_terminate_game);
    tcase_add_test(tc, test_end_game);
    tcase_add_test(tc, test_rotate_another_figure);
    tcase_add_test(tc, test_init_info_if_need);
    tcase_add_test(tc, test_rotate_smashboy);
    tcase_add_test(tc, test_user_input_action);




    suite_add_tcase(s, tc);

    return s;
}



int main(void)
{
    Suite *s = test_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed != 0;
}