#ifndef StageServerStart_h_
#define StageServerStart_h_

#include "Stage.h"

namespace bali
{
    class StageServerStart : public Stage
    {
    public:
        StageServerStart(Game* game, uint32_t uid);
        ~StageServerStart();

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
