#ifndef StageServerLobby_h_
#define StageServerLobby_h_

#include "GameStage.h"


#define STAGE_SERVER_LOBBY_SUCCESS 0
#define STAGE_SERVER_LOBBY_ERROR   1

namespace bali
{
    class CommEvent;
    class StageServerLobby : public GameStage
    {
    public:
        StageServerLobby(Game & game, uint32_t uid);
        ~StageServerLobby();

        uint32_t initialize();
        uint32_t doRemoteEvents(CommEvent & event);
        uint32_t doWindowEvents(sf::Event & wevent);
        uint32_t doLocalInputs();
        uint32_t doLoop();
        uint32_t doDraw();
        uint32_t cleanup();
    private:
    };
}//end namespace bali

#endif
