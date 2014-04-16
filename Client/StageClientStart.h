#ifndef StageClientStart_h_
#define StageClientStart_h_

#include "Stage.h"
#include <SFGUI/sfgui.hpp>
#include "CompWindowStart.h"

namespace bali
{
    class StageClientStart : public Stage
    {
    public:
        StageClientStart(Game* game, uint32_t uid);
        ~StageClientStart();

        uint32_t initialize();
        uint32_t doRemoteEvent(CommEvent & event);
        uint32_t doWindowEvent(sf::Event & event);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();
    private:
        CompWindowStart compStartWindow;

    };
}

#endif // StageClientStart_h_

