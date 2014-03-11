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
        StageServerLobby(Game & game, sf::Uint32 uid);
        ~StageServerLobby();

        sf::Uint32 initialize();
        sf::Uint32 doRemoteEvents(CommEvent & cevent);
        sf::Uint32 doWindowEvents(sf::Event & wevent);
        sf::Uint32 doLocalInputs();
        sf::Uint32 doLoop();
        sf::Uint32 doDraw();
        sf::Uint32 cleanup();
    private:
    };
}//end namespace bali

#endif
