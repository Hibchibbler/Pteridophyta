#ifndef ContextClient_h_
#define ContextClient_h_

#include "Comm.h"
#include "ManagerTile.h"
#include "ManagerConfiguration.h"
#include "ManagerMap.h"
#include "ManagerWorld.h"

namespace bali{

    class ContextClient{
    public:

        std::string mapName;

        //Resolution picks
        uint32_t screenWidth;
        uint32_t screenHeight;

        sf::RenderWindow window;

        sfg::SFGUI sfGui;
        sfg::Desktop desk;

        Comm client;

        ManagerConfiguration mc;
        ManagerMap mm;
        ManagerTile mt;
        ManagerWorld mw;
        ManagerPlayer mp;
    };

}//end namespace bali
#endif

