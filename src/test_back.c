#include "backend.h"
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20





int main (){
    GameInfo_t* game_info;
    
// int state;
//while (state != attaching){
    // while (state != collision){
    // state = get_state();
    //}

//}
    return 0;
}

MainGameState_t* GetMainState(){

} //??

void InitGame(GameInfo_t* game_info){
    game_info->field = InitMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    game_info->score = 0; // потом надо в отдельном файле хранить максимум 
    game_info->level = 0;
}

void userInput(UserAction_t action, bool hold){

}


void TetrisStateMachineUpdate(GameState_t game_state){

    switch(game_state){
        case Initial:
            if()

        // юзер экш старт?
        // инициаллизация поля нулями 
        // инициал параметров 
        // задача скорости
        break;


        case Spawn:
        // создание фигуры текущей и будущей 
        // вывод фигуры на поле графичеески и с помощью единиц на беке
        break;


        case Moving:
        Left,
        Right,
        Down,
        // изменение координат текущей фигуры 

        break;


        case Rotating:
        // изменение координат текущей фигуры 
        break;


        case Shifting:
        // по сути сначала шифтинг а потом задача действий 
        // изменение координат текущей фигуры 
        break;


        case Attaching:
        // соприкосновение с фигурой 
        break;

        case Clearing:
        // удаление линии в случае ее заполнения 
        // Shifting всех линий выше
        // изменение параметров игры 
        break;

        case GameOver:
        //фигура не влезла 

        break;
    }
}

void GetUserAction(UserAction_t action){
    switch(action){
        case Start:

   
        break;
    }

    // нужен ретерн значения экшен
   
}