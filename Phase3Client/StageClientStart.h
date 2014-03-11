#ifndef StageClientStart_h_
#define StageClientStart_h_

#include "GameStage.h"
#include <SFGUI/sfgui.hpp>

namespace bali
{
    class StageClientStart : public GameStage
    {
    public:
        StageClientStart(Game & game, sf::Uint32 uid);
        ~StageClientStart();

        sf::Uint32 initialize();
        sf::Uint32 doRemoteEvents(CommEvent & cevent);
        sf::Uint32 doWindowEvents(sf::Event & wevent);
        sf::Uint32 doLocalInputs();
        sf::Uint32 doLoop();
        sf::Uint32 doDraw();
        sf::Uint32 cleanup();
    private:
        sfg::Window::Ptr setupWindow;
        sfg::Desktop setupDesktop;

        sfg::Entry::Ptr ipEntry;//Kept to retrieve later
        sfg::Entry::Ptr passEntry;//Kept to retrieve later
        sfg::Entry::Ptr portEntry;//Kept to retrieve later
        sfg::Entry::Ptr nameEntry;//Kept to retrieve later
        void doStart();
    };
}

#endif // StageClientStart_h_

