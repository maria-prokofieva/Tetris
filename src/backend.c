#include "backend.h"
#include "common.h"

MainGameState_t* GetMainGameInfo() {
    static MainGameState_t game_state = {0};
    return &game_state;
}

void userInput(UserAction_t action, bool hold){
    MainGameState_t* game_state = GetMainGameInfo();
    switch(action){
        case Start:
            if(game_state->current_state == Waiting){;
                game_state->current_state = Initial;
            }

        break;
        
        case Right:
            if(game_state->current_state == Moving && (game_state->game->pause == Unpaused)){
                MoveRight(game_state->game, game_state->figure);
            }
        break;

        case Left:
            if(game_state->current_state == Moving && (game_state->game->pause == Unpaused)){
                MoveLeft(game_state->game, game_state->figure);
            }    
        break;

        case Down:
            if(game_state->current_state == Moving && (game_state->game->pause == Unpaused)){
                if(MoveDownToTheEnd(game_state->game, game_state->figure) == MoveDownCollision){
                    game_state->current_state = Collision;
                }
            }    
        break;

        case Action:
            if((game_state->game->pause == Unpaused) && game_state->current_state == Moving){
                game_state->current_state = Rotating;
                RotateFigure(game_state->game, game_state->figure);
                game_state->current_state = Moving;
            }
        break;
            
        case Pause:
            PauseGame(game_state->game);
        break;

    }
}

void PauseGame(GameInfo_t* game){
    game->pause = !(game->pause);
}

void InitRandom(){
    srand(time(NULL));
}

GameInfo_t updateCurrentState(){
    MainGameState_t* game_state = GetMainGameInfo();
    InitInfoIfNeed(game_state);
    TetrisFsm(game_state);
    return *(game_state->game);
}

int GenerateRandomNum(int max_num){
    int random_num = rand() % max_num;
    return random_num;
}

int** InitMatrix(int rows, int cols){
    int** matrix = malloc(rows * sizeof(int*)); // нужна ли проверка malloc на 0
    for(int i = 0; i < rows; i++){
        matrix[i] = malloc(cols * sizeof(int));
        for(int j = 0; j < cols; j++){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void SetMatrixToZero(int** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = 0;
        }
    }
}



void UpdateCurrentFigure(FigureInfo_t* figure){
    if (!figure || !figure->current_figure) {
        fprintf(stderr, "ERROR HERE\n");
        exit(1);
    }

    figure->y = 0;
    figure->x = FIELD_WIDTH / 2 - 2;
    figure->angle = Degree0;
}

void InitInfoIfNeed(MainGameState_t* game_state){
    if(game_state->game == NULL){
        game_state->game = malloc(sizeof(GameInfo_t));
        game_state->game->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
        InitRandom();
        game_state->game->pause = Unpaused;
    }
} 

void InitFigureIfNeed(MainGameState_t* game_state){
    if(game_state->figure == NULL){
        game_state->figure = malloc(sizeof(FigureInfo_t));
        game_state->figure->current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
        game_state->figure->temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
        game_state->figure->y = 0;
        game_state->figure->x = FIELD_WIDTH / 2 - 2;
        game_state->figure->angle = Degree0;
    }
}



void CopyStaticMatrixToDynamic(int rows, int cols, int **matrix, int(*copied_matrix)[cols]){
    for (int i = 0; i < rows; i++){
        for  (int j = 0; j < cols; j++){
            matrix[i][j] = copied_matrix[i][j];
        }
    }
}

void GenerateSmashboy(int** current_figure){
    int smashboy_matrix[FIGURE_ROWS][FIGURE_COLS] = { 
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    CopyStaticMatrixToDynamic(FIGURE_ROWS, FIGURE_COLS, current_figure, smashboy_matrix);

}

void GenerateHero(int** current_figure){
    int hero_matrix[FIGURE_ROWS][FIGURE_COLS] = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    CopyStaticMatrixToDynamic(FIGURE_ROWS, FIGURE_COLS, current_figure, hero_matrix);
}

void GenerateRhodeIsland(int** current_figure){
    int rhode_island_matrix[FIGURE_ROWS][FIGURE_COLS] = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    CopyStaticMatrixToDynamic(FIGURE_ROWS, FIGURE_COLS, current_figure, rhode_island_matrix);
}

void GenerateCleveland(int** current_figure){
    int cleveland_matrix[FIGURE_ROWS][FIGURE_COLS] = {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    CopyStaticMatrixToDynamic(FIGURE_ROWS, FIGURE_COLS, current_figure, cleveland_matrix);
}

void GenerateOrangeRicky(int** current_figure){
    int orange_ricky_matrix[FIGURE_ROWS][FIGURE_COLS] = {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    CopyStaticMatrixToDynamic(FIGURE_ROWS, FIGURE_COLS, current_figure, orange_ricky_matrix);
}

void GenerateBlueRicky(int** current_figure){
    int blue_ricky_matrix[FIGURE_ROWS][FIGURE_COLS] = {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    CopyStaticMatrixToDynamic(FIGURE_ROWS, FIGURE_COLS, current_figure, blue_ricky_matrix);
}

void GenerateTeewee(int** current_figure){
    int teewee_matrix[FIGURE_ROWS][FIGURE_COLS] = {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    CopyStaticMatrixToDynamic(FIGURE_ROWS, FIGURE_COLS, current_figure, teewee_matrix);
}

void GenerateTetromino(int random_num, FigureInfo_t* figure){ 
    switch (random_num){
        case Smashboy:
            GenerateSmashboy(figure->current_figure);
        break;
        
        case Hero:
            GenerateHero(figure->current_figure);
        break;

        case RhodeIsland:
            GenerateRhodeIsland(figure->current_figure);
        break;

        case Cleveland:
            GenerateCleveland(figure->current_figure);
        break;

        case OrangeRicky:
            GenerateOrangeRicky(figure->current_figure);
        break;

        case BlueRicky:
            GenerateBlueRicky(figure->current_figure);
        break;

        case Teewee:
            GenerateTeewee(figure->current_figure);
        break;
    }
}


void GenerateNewFigure(MainGameState_t *game_state){
    //int random_num = GenerateRandomNum(MAX_NUM_FIGURES);
    int random_num = GenerateRandomNum(MAX_NUM_FIGURES);
    game_state->figure->current_type = random_num;
    GenerateTetromino(random_num, game_state->figure);
}






void PrintField(GameInfo_t* game){
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j <  FIELD_WIDTH; j++){
            printf("%d", game->field[i][j]);
        }
       printf("\n");
    }
        printf("\n");
}




void ClearFigureFromGameField(GameInfo_t *game, FigureInfo_t *figure){
    int y = figure->y;
    for(int i = 0; i < FIGURE_ROWS; i++){
        int x = figure->x;
        for(int j = 0; j < FIGURE_COLS; j++){
            if(figure->current_figure[i][j] && y >= 0){
                game->field[y][x] = 0;
            }
            x++;
        }
        y++;
    }
}


void AddFigureToField(GameInfo_t* game, int** matrix, FigureInfo_t* figure){
    int figure_y = figure->y;
    for(int i = 0; i < FIGURE_ROWS; i++){
        int figure_x = figure->x;
        for(int j = 0; j < FIGURE_COLS; j++){
            if(matrix[i][j] == 1 && figure_y >= 0 && figure_x >= 0){
                game->field[figure_y][figure_x] = 1;
            }
            figure_x++;
        }
        figure_y++;
    }
}


int MoveDown(GameInfo_t *game, FigureInfo_t* figure){
    int status = MoveDownOk;
    if(game->pause == Unpaused){
        ClearFigureFromGameField(game, figure);
        figure->y++;
        if(CheckCollision(game, figure->current_figure, figure->y, figure->x)){
            figure->y--;
            AddFigureToField(game, figure->current_figure, figure);
            status = MoveDownCollision;
        }
        if(status == MoveDownOk){   
            AddFigureToField(game, figure->current_figure, figure);
        }
    }
        return status;
}

int MoveDownToTheEnd(GameInfo_t *game, FigureInfo_t* figure){
    int status = MoveDownOk;
    while(status != MoveDownCollision) {
       status = MoveDown(game, figure);
    }
    return status;
}
                

int CheckCollision(GameInfo_t* game, int** matrix, int y, int x){
    int status = false;
    for(int i = 0; i < FIGURE_ROWS; i++){
        for(int j = 0; j < FIGURE_COLS; j++){
            if(matrix[i][j]){
                int new_y = y + i;
                int new_x = x + j;
                if(new_y < 0 || new_y >= FIELD_HEIGHT || new_x < 0 || new_x >= FIELD_WIDTH){
                    status = true;
                } else if(game->field[new_y][new_x]){
                    status = true;
                }
            }
        }
    }
    return status;
}


int CheckRightSide(GameInfo_t* game, FigureInfo_t* figure){
    int status = false;
    int y = figure->y;
    for(int  i = 0; i < FIGURE_ROWS; i++){ 
        int x = figure->x;
        if (!status){
            for(int j = 0; j < FIGURE_COLS; j++){
                if(figure->current_figure[i][j]){ 
                    if(y >= 0){
                        if(x + 1 == FIELD_WIDTH){
                            status = true;
                        } else if(game->field[y][x + 1]){
                            status = true;
                        }
                    }
                    
                }
                x++;
            }
        }
        y++;
    }
    return status;
}


int CheckLeftSide(GameInfo_t* game, FigureInfo_t* figure){
    int status = false;
    int y = figure->y;
    for(int  i = 0; i < FIGURE_ROWS; i++){ 
        int x = figure->x;
        if (!status){
            for(int j = 0; j < FIGURE_COLS; j++){
                if(figure->current_figure[i][j]){ 
                    if(y >= 0){
                        if(x - 1 < 0){
                            status = true;
                        } else if(game->field[y][x - 1]){
                                status = true;
                        }
                    }
                }
                x++;
            }
        }
        y++;
    }
    return status;
}


void MoveRight(GameInfo_t* game, FigureInfo_t* figure){
        ClearFigureFromGameField(game, figure);
        if(!CheckRightSide(game, figure)){
            figure->x++;
        }
        AddFigureToField(game, figure->current_figure, figure);
}

void MoveLeft(GameInfo_t* game, FigureInfo_t* figure){
        ClearFigureFromGameField(game, figure);
        if(!CheckLeftSide(game, figure)){
            figure->x--;
        }
        AddFigureToField(game, figure->current_figure, figure);
    }


int IsFilledLine(int** field, int row_num){
    int status = 0;
    int cnt_filled = 0;
    for(int j = 0; j < FIELD_WIDTH; j++){
        if(field[row_num][j]){
            cnt_filled++;
        }
        if(cnt_filled == 10){
            status = 1;
        }
    }
    return status;
}

void ClearLines(int** field){
    for(int i = FIELD_HEIGHT - 1; i > 0 ; i--){
        if(IsFilledLine(field, i)){
            MoveLinesDown(field, i - 1);
            i++;
        }
    }
}

void MoveLinesDown(int** field, int row_num){
    for(int i = row_num; i >= 0; i--){
        for(int j = 0; j < FIELD_WIDTH; j++){
            field[i + 1][j] = field[i][j];
        }
    }
    for (int j = 0; j < FIELD_WIDTH; j++) {
        field[0][j] = 0;
    }
}

void RotateFigure(GameInfo_t* game, FigureInfo_t* figure){ 
    int  n = 0;
    if(figure->current_type != Hero){
        n = 1;
    }
    int num = FIGURE_COLS - 1 - n;
    for(int i = 0; i < FIGURE_ROWS - n; i++){ 
        for(int j = 0; j < FIGURE_COLS - n; j++){
            figure->temp_matrix[j][num - i] = figure->current_figure[i][j];
        }
    }
    ClearFigureFromGameField(game, figure);
    switch (figure->current_type){

        case Smashboy:
            break;
    
        case Hero:
            RotateHero(game, figure);
            break;

        default:
            RotateAnotherFigures(game, figure);
            break;

    }

    AddFigureToField(game, figure->current_figure, figure);
}
            
void RotateHero(GameInfo_t* game, FigureInfo_t* figure){
    int hero_kicks[4][5][2] = {
        {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
        {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
        {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
        {{0, 0},{1, 0},{-2, 0},{1, -2},{-2, 1}}
    };

    for(int k = 0; k < 5; k++){
        int new_y =  figure->y + hero_kicks[figure->angle][k][1]; 
        int new_x = figure->x + hero_kicks[figure->angle][k][0];
        if(!CheckCollision(game, figure->temp_matrix, new_y, new_x)){
            for(int i = 0; i < FIGURE_ROWS; i++){
                for(int j = 0; j < FIGURE_COLS; j++){
                    figure->current_figure[i][j] = figure->temp_matrix[i][j];
                }
            } 
            if(figure->angle == Degree270){
                figure->angle = Degree0;
            } else{
                figure->angle++;
            }
            figure->y = new_y;
            figure->x = new_x;
            break;           
        } 
    }

}


void RotateAnotherFigures(GameInfo_t* game, FigureInfo_t* figure){
    int another_kicks[4][5][2] = {
       {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
       {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
       {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
       {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}
    };

    for(int k = 0; k < 5; k++){
        int new_y =  figure->y + another_kicks[figure->angle][k][1]; 
        int new_x = figure->x + another_kicks[figure->angle][k][0];
        if(!CheckCollision(game, figure->temp_matrix, new_y, new_x)){
            for(int i = 0; i < FIGURE_ROWS-1; i++){
                for(int j = 0; j < FIGURE_COLS-1; j++){
                    figure->current_figure[i][j] = figure->temp_matrix[i][j];
                }
            } 
            if(figure->angle == Degree270){
                figure->angle = Degree0;
            } else{
                figure->angle++;
            }
            figure->y = new_y;
            figure->x = new_x;
            break;           
        } 
    }

}
    

void TetrisFsm(MainGameState_t *game_state){
    switch (game_state->current_state){
        case Waiting:
            break;

        case Initial:
            InitFigureIfNeed(game_state);
            game_state->current_state = Spawn;
            break;

        case Spawn:
            GenerateNewFigure(game_state);
            UpdateCurrentFigure(game_state->figure);
            if(CheckCollision(game_state->game, game_state->figure->current_figure, game_state->figure->y, game_state->figure->x)){
                game_state->current_state = GameOver;
                break;
            } 
            AddFigureToField(game_state->game, game_state->figure->current_figure, game_state->figure);
            game_state->current_state = Moving;
            break;

        case Moving:
            int status =  MoveDown(game_state->game, game_state->figure);
            if(status == MoveDownCollision){
                game_state->current_state = Collision;
            }
            break;

        case Collision:
            game_state->current_state = Clearing;
           // UpdateCurrentFigure(game_state->figure);
            break;
    
        case Clearing:
            ClearLines(game_state->game->field);
            game_state->current_state = Spawn;
            break;

        case Rotating:
            break;

        case GameOver:
            // ЗАСТАВКА
            game_state->game->pause = GameOverPause;
            break;

        default:
            break;
    }
    
}

void FreeMatrix(int** matrix, int row){
    if(matrix){
        for(int i = 0; i < row; i++){
            free(matrix[i]);
        }
        free(matrix);
    }
}

void TerminateGame(MainGameState_t* game_state){ 
    FreeMatrix(game_state->game->field, FIELD_HEIGHT);
    game_state->game->field = NULL; 
    free(game_state->game);
    game_state->game = NULL;
    FreeMatrix(game_state->figure->current_figure, FIGURE_ROWS);
    game_state->figure->current_figure = NULL;
    FreeMatrix(game_state->figure->temp_matrix, FIGURE_ROWS);
    game_state->figure->temp_matrix = NULL;
    free(game_state->figure);
    game_state->figure = NULL;
}
       
void EndGame(){
    MainGameState_t* game_state = GetMainGameInfo();
    TerminateGame(game_state);
}