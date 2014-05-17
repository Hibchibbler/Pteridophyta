#ifndef StageClientLobby_h_
#define StageClientLobby_h_

#include "Stage.h"
#include <SFGUI\SFGUI.hpp>
#include "CompWindowLobby.h"

namespace bali{
    class StageClientLobby : public Stage
    {

    public:
        StageClientLobby(Game* game, uint32_t uid);
        ~StageClientLobby();

        ReturnVal initialize();
        ReturnVal doRemoteEvent(CommEvent & event);
        ReturnVal doWindowEvent(sf::Event & event);
        ReturnVal doLocalInputs();
        ReturnVal doUpdate();
        ReturnVal doDraw();
        ReturnVal cleanup();
        uint32_t processCommands(void* arg);
    private:
        sf::Clock           sendWhoIsClk;


    };
}//end namespace bali
#endif
