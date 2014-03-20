#ifndef ServerGame_h_
#define ServerGame_h_

#include "Game.h"
namespace bali
{
    //this is a server-side game object
    class ServerGame : public Game
    {
    public:
        ServerGame();
        ~ServerGame();
        sf::Uint32 initialize();
        sf::Uint32 doEventProcessing();
        sf::Uint32 doGameProcessing();
        sf::Uint32 cleanup();
    private:

    };
}
#endif // ServerGame_h_
