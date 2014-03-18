#include <iostream>
#include "GameServer.h"
using namespace std;
using namespace bali;
int main()
{
    Game* game =  new GameServer();
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
