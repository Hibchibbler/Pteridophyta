#ifndef StageServerMain_h_
#define StageServerMain_h_

#include "GameStage.h"

namespace bali
{
    class StageServerMain : public GameStage
    {
    public:
        StageServerMain(Game & game, uint32_t uid);
        ~StageServerMain();

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
