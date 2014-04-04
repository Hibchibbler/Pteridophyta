#ifndef StageClientStart_h_
#define StageClientStart_h_

#include "GameStage.h"
#include <SFGUI/sfgui.hpp>
#include "CompStartWindow.h"

namespace bali
{
    class StageClientStart : public GameStage
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
        CompStartWindow compStartWindow;

    };
}

#endif // StageClientStart_h_

