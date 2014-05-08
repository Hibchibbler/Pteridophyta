#ifndef GameServer_h_
#define GameServer_h_

#include "Game.h"
#include "ContextServer.h"

#define GAME_SERVER_SUCCESS 0
#define GAME_SERVER_ERROR   1

namespace bali
{
    //this is a server-side game object
    class GameServer : public Game
    {
    public:
        GameServer();
        ~GameServer();
        uint32_t initialize();
        uint32_t doEventProcessing();
        uint32_t doGameProcessing();
        uint32_t cleanup();
        uint32_t processCommands(void* arg){}

    private:
    };
}
#endif // GameServer_h_
