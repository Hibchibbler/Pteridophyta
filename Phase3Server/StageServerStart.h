#ifndef StageServerStart_h_
#define StageServerStart_h_

#include "GameStage.h"

namespace bali
{
    class StageServerStart : public GameStage
    {
    public:
        StageServerStart(Game & game, sf::Uint32 uid);
        ~StageServerStart();

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
