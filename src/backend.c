#include "backend.h"


GameInfo_t* GetGameInfo() {
    static GameInfo_t game = {0};
    return &game;
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

void InitFigure(FigureInfo_t* figure){
    figure->current_figure = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
    figure->y = -1;
    figure->x = FIELD_WIDTH / 2 - 2;
}

void UpdateCurrentFigure(FigureInfo_t* figure){
    if (!figure || !figure->current_figure) {
        fprintf(stderr, "ERROR HERE\n");
        exit(1);
    }

    figure->y = -1;
    figure->x = FIELD_WIDTH / 2 - 2;
}

void InitGameInfo(GameInfo_t* game){
    game->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    game->state = Initial;
    game->figure = malloc(sizeof(FigureInfo_t));
    InitFigure(game->figure);
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


void GenerateNewFigure(FigureInfo_t* figure, GameInfo_t* game){
    if (!game->figure || !game->figure->current_figure) {
        fprintf(stderr, "ERROR HERE\n");
        exit(1);
    }
    //int random_num = GenerateRandomNum(MAX_NUM_FIGURES);
    int random_num = GenerateRandomNum(7);
    game->figure->current_type = random_num;
    GenerateTetromino(random_num, figure);
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




void ClearFigureFromGameField(GameInfo_t *game, int** matrix){
    int y = game->figure->y;
    for(int i = 0; i < FIGURE_ROWS; i++){
        int x = game->figure->x;
        for(int j = 0; j < FIGURE_COLS; j++){
            if(matrix[i][j] && y >= 0){
                game->field[y][x] = 0;
            }
            x++;
        }
        y++;
    }
}


void AddFigureToField(GameInfo_t* game, int** matrix){
    int figure_y = game->figure->y;
    for(int i = 0; i < FIGURE_ROWS; i++){
        int figure_x = game->figure->x;
        for(int j = 0; j < FIGURE_COLS; j++){
            if(matrix[i][j] == 1 && figure_y >= 0 && figure_x >= 0){
                game->field[figure_y][figure_x] = 1;
            }
            figure_x++;
        }
        figure_y++;
    }
}


int MoveDown(GameInfo_t *game){
    int status = 1;
    ClearFigureFromGameField(game, game->figure->current_figure);
    if(CheckCollision(game, game->figure->current_figure)){
        AddFigureToField(game, game->figure->current_figure);
        game->state = Collision;
        status = 0;
    }
    if(status){  
        game->figure->y++;   
        AddFigureToField(game, game->figure->current_figure);
    }
    return status;
}
                

int CheckCollision(GameInfo_t* game, int** matrix){
    int status = false;
    int y = game->figure->y;
    for(int  i = 0; i < FIGURE_ROWS; i++){ 
        int x = game->figure->x;
        if (!status){
            for(int j = 0; j < FIGURE_COLS; j++){
                if(matrix[i][j]){ 
                    if(y + 1 >= 0){
                        if(y + 1 >= FIELD_HEIGHT){
                            status = true; 
                        } else if (game->field[y + 1][x]){
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


int CheckRightSide(GameInfo_t* game){
    int status = false;
    int y = game->figure->y;
    for(int  i = 0; i < FIGURE_ROWS; i++){ 
        int x = game->figure->x;
        if (!status){
            for(int j = 0; j < FIGURE_COLS; j++){
                if(game->figure->current_figure[i][j]){ 
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


int CheckLeftSide(GameInfo_t* game){
    int status = false;
    int y = game->figure->y;
    for(int  i = 0; i < FIGURE_ROWS; i++){ 
        int x = game->figure->x;
        if (!status){
            for(int j = 0; j < FIGURE_COLS; j++){
                if(game->figure->current_figure[i][j]){ 
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


void MoveRight(GameInfo_t* game){
    ClearFigureFromGameField(game, game->figure->current_figure);
    if(!CheckRightSide(game)){
        game->figure->x++;
    }
    AddFigureToField(game, game->figure->current_figure);
}

void MoveLeft(GameInfo_t* game){
    ClearFigureFromGameField(game, game->figure->current_figure);
    if(!CheckLeftSide(game)){
        game->figure->x--;
        
    }
    AddFigureToField(game, game->figure->current_figure);
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

int IsRotates(GameInfo_t* game, int** temp_matrix){ 
    int status = 0;
    int num = FIGURE_COLS - 1;
    if(game->figure->current_type != Smashboy){
        if(game->figure->current_figure){
            temp_matrix = InitMatrix(FIGURE_ROWS, FIGURE_COLS);
            for(int i = 0; i < FIGURE_ROWS; i++){
                for(int j = 0; j < FIGURE_COLS; j++){
                    temp_matrix[j][num - i] = game->figure->current_figure[i][j];
                }
            }
            ClearFigureFromGameField(game, game->figure->current_figure);
            if(!CheckCollision(game, temp_matrix)){
                for(int i = 0; i < FIGURE_ROWS; i++){
                    for(int j = 0; j < FIGURE_COLS; j++){
                    game->figure->current_figure[i][j] = temp_matrix[i][j];
                    }
                }
                status = 1;
            } 
        }
    }
    return status;
}

