#ifndef StageServerLobby_h_
#define StageServerLobby_h_

#include "Stage.h"


#define STAGE_SERVER_LOBBY_SUCCESS 0
#define STAGE_SERVER_LOBBY_ERROR   1

namespace bali
{
    class CommEvent;
    class StageServerLobby : public Stage
    {
    public:
        StageServerLobby(Game* game, uint32_t uid);
        ~StageServerLobby();

        uint32_t initialize();
        uint32_t doRemoteEvent(CommEvent & event);
        uint32_t doWindowEvent(sf::Event & event);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();
    private:
    };
}//end namespace bali

#endif
