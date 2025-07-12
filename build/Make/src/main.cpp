#include "Game/Game.h"

// Game main, will be used when compiling Games for Windows
int main(int argc, char* argv[]){    
    Game game;

    if (game.Initialize() < 0) return -1;
    game.Run();
    game.Destroy();

    return 0;
}