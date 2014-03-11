#ifndef GameServer_h_
#define GameServer_h_

#include "Game.h"
#include "Comm.h"

#include "ContextServer.h"

#include "ManagerTexture.h"
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
        sf::Uint32 initialize();
        sf::Uint32 doEventProcessing();
        sf::Uint32 doGameProcessing();
        sf::Uint32 cleanup();

        Comm server;

        ManagerConfiguration mc;
        ManagerMap mm;
        ManagerTexture mt;
        ManagerWorld mw;
        ManagerPlayer mp;
    private:

    };
}
#endif // GameServer_h_
