#ifndef GameClient_h_
#define GameClient_h_

#include <SFML\graphics.hpp>
#include "Game.h"
#include "Comm.h"

#include "ContextClient.h"
#include "ManagerTexture.h"
#include "ManagerConfiguration.h"
#include "ManagerMap.h"
#include "ManagerWorld.h"

namespace bali
{


    //this is the client-side game object.
    class GameClient : public Game
    {
    public:
        GameClient();
        ~GameClient();
        sf::Uint32 initialize();
        sf::Uint32 doEventProcessing();
        sf::Uint32 doGameProcessing();
        sf::Uint32 cleanup();

        sf::RenderWindow window;
        sf::Uint32 winHeight;
        sf::Uint32 winWidth;
        sfg::SFGUI sfgui;

        Comm client;

        ManagerConfiguration mc;
        ManagerMap mm;
        ManagerTexture mt;
        ManagerWorld mw;
        ManagerPlayer mp;

        sfg::SFGUI sfGui;
        sfg::Desktop desk;

    private:
    };
}
#endif // GameClient_h_
