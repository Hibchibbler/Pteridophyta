#ifndef Context_h_
#define Context_h_

#include "Comm.h"
#include "ManagerTile.h"
#include "ManagerConfiguration.h"
#include "ManagerMap.h"
#include "ManagerWorld.h"
#include "ManagerPlayer.h"
#include "Commandable.h"
#include "CommandContext.h"
#include <SFGUI/SFGUI.hpp>

namespace bali{

///This class is the primary interface to change game state, and to get game state.
class Context : public Commandable
{
public:
    Comm net;
    ManagerConfiguration mc;
    ManagerMap mm;
    ManagerTile mt;
    ManagerWorld mw;
    ManagerPlayer mp;

    //TODO: tie these up
    std::string mapName;
    //Resolution picks
    uint32_t screenWidth;
    uint32_t screenHeight;
    sf::RenderWindow window;
    sfg::SFGUI sfGui;

    uint32_t processCommands(void* arg){ return 0; }
};

}//end namespace bali
#endif

