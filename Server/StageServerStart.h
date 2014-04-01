#ifndef StageServerStart_h_
#define StageServerStart_h_

#include "GameStage.h"

namespace bali
{
    class StageServerStart : public GameStage
    {
    public:
        StageServerStart(Game* game, uint32_t uid);
        ~StageServerStart();

        uint32_t initialize();
        uint32_t doRemoteEvent(CommEvent & event);
        uint32_t doWindowEvents(sf::Event & wevent);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();
    private:
    };
}//end namespace bali

#endif
