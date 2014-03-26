#ifndef GameClient_h_
#define GameClient_h_

#include <SFML\graphics.hpp>
#include "Game.h"
#include "Comm.h"

#include "ContextClient.h"
//#include "ManagerTexture.h"
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
        uint32_t initialize();
        uint32_t doEventProcessing();
        uint32_t doGameProcessing();
        uint32_t cleanup();

        sf::RenderWindow window;
        sfg::SFGUI sfGui;

        Comm client;

        ManagerConfiguration mc;
        ManagerMap mm;
        //ManagerTexture mt;
        ManagerWorld mw;
        ManagerPlayer mp;

        sfg::Desktop desk;

        sf::VertexArray layer1;

    private:
    };
}
#endif // GameClient_h_
