#include "GameClient.h"
#include "Game.h"
#include <SFML/Window.hpp>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
using namespace bali;


int main()
{

    Game* game =  new GameClient();
    bool done = false;

    game->initialize();

    while (!done){
        uint32_t ret;

        ret = game->doEventProcessing();
        if (ret){
            done = true;
            continue;
        }

        ret = game->doGameProcessing();
        if (ret){
            done = true;
            continue;
        }
    }

    game->cleanup();

    return 0;
}

