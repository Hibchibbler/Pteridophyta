#ifndef GameServer_h_
#define GameServer_h_

#include "Game.h"
#include "Comm.h"

#include "ContextServer.h"

//#include "ManagerTexture.h"
#include "ManagerConfiguration.h"
#include "ManagerMap.h"
#include "ManagerWorld.h"
#include "ManagerPlayer.h"

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

        Comm server;

        ManagerConfiguration mc;
        ManagerMap mm;
        //ManagerTexture mt;
        ManagerWorld mw;
        ManagerPlayer mp;
    private:

    };
}
#endif // GameServer_h_
