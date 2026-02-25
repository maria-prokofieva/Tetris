#include "backend.h"
#include "common.h"

MainGameState_t* GetMainGameInfo() {
    static MainGameState_t game_state = {0};
    return &game_state;
}

void userInput(UserAction_t action, bool hold){
    //GameInfo_t *game = updateCurrentState();
    //printf("In UI\n");
    MainGameState_t* game_state = GetMainGameInfo();
    switch(action){
        case Start:
            if(game_state->current_state == Waiting){;
                game_state->current_state = Initial;
            }

        break;
        
        case Right:
            if(game_state->current_state == Moving){
                MoveRight(game_state->game, game_state->figure);
            }
        break;

        case Left:
            if(game_state->current_state == Moving){
                MoveLeft(game_state->game, game_state->figure);
            }    
        break;

        case Down:
            if(game_state->current_state == Moving){
                MoveDownToTheEnd(game_state->game, game_state->figure);
            }    


    }
}

GameInfo_t updateCurrentState(){
    MainGameState_t* game_state = GetMainGameInfo();
    InitGameInfoIfNeed(game_state);
    TetrisFsm(game_state);
    return *(game_state->game);
}

int GenerateRandomNum(int max_num){
    int random_num = rand() % max_num;
    return random_num;
}

int** InitMatrix(int rows, int cols){
    int** matrix = malloc(rows * sizeof(int*)); 
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
}

void InitGameInfoIfNeed(MainGameState_t* game_state){
    if(game_state->game == NULL){
        game_state->game = malloc(sizeof(GameInfo_t));
        game_state->game->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    }
} 

void InitFigureIfNeed(MainGameState_t* game_state){
    if(game_state->figure == NULL){
        game_state->figure = malloc(sizeof(FigureInfo_t));
        game_state->figure->current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
        game_state->figure->y = -1;
        game_state->figure->x = FIELD_WIDTH / 2 - 2;
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
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    CopyStaticMatrixToDynamic(FIGURE_ROWS, FIGURE_COLS, current_figure, smashboy_matrix);

}

void GenerateHero(int** current_figure){
    int hero_matrix[FIGURE_ROWS][FIGURE_COLS] = {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
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
    int random_num = GenerateRandomNum(7);
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
    ClearFigureFromGameField(game, figure);
    figure->y++;
    if(CheckCollision(game, figure->current_figure, figure)){
        figure->y--;
        AddFigureToField(game, figure->current_figure, figure);
        status = MoveDownCollision;
    }
    if(status == MoveDownOk){   
        AddFigureToField(game, figure->current_figure, figure);
    }
    return status;
}

void MoveDownToTheEnd(GameInfo_t *game, FigureInfo_t* figure){
    int status = 0;
    while(status != MoveDownCollision) {
       status = MoveDown(game, figure);
    }
}
                

int CheckCollision(GameInfo_t* game, int** matrix, FigureInfo_t* figure){
    int status = false;
    for(int i = 0; i < FIGURE_ROWS; i++){
        for(int j = 0; j < FIGURE_COLS; j++){
            if(matrix[i][j]){
                int y = figure->y + i;
                int x = figure->x + j;
                if(y < 0 || y >= FIELD_HEIGHT || x < 0 || x >= FIELD_WIDTH){
                    status = true;
                } else if(game->field[y][x]){
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
                        if(x + 1 == 10){
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
                        if(x - 1 == -1){
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

int RotateFigure(GameInfo_t* game, FigureInfo_t* figure, int** temp_matrix){ 
    int status = 0;
    int num = FIGURE_COLS - 1;
    if(figure->current_type != Smashboy && figure->current_type != Hero){
            temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
            for(int i = 0; i < FIGURE_ROWS; i++){
                for(int j = 0; j < FIGURE_COLS; j++){
                    temp_matrix[j][num - i] = figure->current_figure[i][j];
                }
            }
            ClearFigureFromGameField(game, figure);
            if(!CheckCollision(game, temp_matrix, figure)){
                for(int i = 0; i < FIGURE_ROWS; i++){
                    for(int j = 0; j < FIGURE_COLS; j++){
                    figure->current_figure[i][j] = temp_matrix[i][j];
                    }
                }
                status = 1;
            } 
        }
    else if(figure->current_type == Hero){
        temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
        for(int i = 0; i < FIGURE_ROWS; i++){
            for(int j = 0; j < FIGURE_COLS; j++){
                temp_matrix[j][num - i] = figure->current_figure[i][j];
            }
        }
        ClearFigureFromGameField(game, figure);
        if(!CheckCollision(game, temp_matrix, figure)){
            for(int i = 0; i < FIGURE_ROWS; i++){
                for(int j = 0; j < FIGURE_COLS; j++){
                figure->current_figure[i][j] = temp_matrix[i][j];
                }
            }
            status = 1;
        } 
    }
            
    return status;
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
            //UpdateCurrentFigure(game_state->figure);
            AddFigureToField(game_state->game, game_state->figure->current_figure, game_state->figure);
            game_state->current_state = Moving;
            break;

        case Moving:
            if(MoveDown(game_state->game, game_state->figure) == MoveDownCollision){
                game_state->current_state = Collision;
            }
            break;

        case Collision:
            game_state->current_state = Clearing;
            UpdateCurrentFigure(game_state->figure);
            break;
    
        case Clearing:
            ClearLines(game_state->game->field);
            game_state->current_state = Spawn;
            break;

        case Rotating:
            

        default:
            break;
    }
    
}