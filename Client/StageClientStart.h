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
        uint32_t doWindowEvents(sf::Event & event);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();
    private:
        CompStartWindow compStartWindow;
//        sfg::Window::Ptr setupWindow;
//        sfg::Desktop setupDesktop;

//        sfg::Entry::Ptr ipEntry;//Kept to retrieve later
//        sfg::Entry::Ptr passEntry;//Kept to retrieve later
//        sfg::Entry::Ptr portEntry;//Kept to retrieve later
//        sfg::Entry::Ptr nameEntry;//Kept to retrieve later
//        void doStart();
    };
}

#endif // StageClientStart_h_

