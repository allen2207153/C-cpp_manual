#include <iostream>
#include"Game.h"


int main(int argc, char** argv)
{
    Game game;
    bool isSuccess = game.Initialize();

    if (isSuccess) {
        game.RunLoop();
    }
    else {
        std::cout << "Faild\n";
    }

    game.Shutdown();

    return 0;
}