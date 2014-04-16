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

        uint32_t initialize();
        uint32_t doRemoteEvent(CommEvent & event);
        uint32_t doWindowEvent(sf::Event & event);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();
    private:
        sf::Clock           sendWhoIsClk;
        CompWindowLobby compLobbyWindow;

    };
}//end namespace bali
#endif
