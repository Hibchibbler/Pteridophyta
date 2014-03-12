#ifndef StageClientLobby_h_
#define StageClientLobby_h_

#include "GameStage.h"
#include <SFGUI\SFGUI.hpp>

namespace bali{
    class StageClientLobby : public GameStage
    {

    public:
        StageClientLobby(Game & game, sf::Uint32 uid);
        ~StageClientLobby();

        sf::Uint32 initialize();
        sf::Uint32 doRemoteEvents(CommEvent & cevent);
        sf::Uint32 doWindowEvents(sf::Event & wevent);
        sf::Uint32 doLocalInputs();
        sf::Uint32 doLoop();
        sf::Uint32 doDraw();
        sf::Uint32 cleanup();
    private:
        sfg::Entry::Ptr     team1[5];
        sfg::Entry::Ptr     team2[5];
        sfg::Window::Ptr    mywindow;//Kept to Show/Hide
        sfg::Box::Ptr       box;//kept to add the spinner later.
        sfg::Button::Ptr    joinTeam1Button;//kept to hide later.
        sfg::Button::Ptr    joinTeam2Button;//kept to hide later.
        sfg::Spinner::Ptr spinner;
        sfg::Label::Ptr msg;

        void doJoinTeam1();
        void doJoinTeam2();



    };
}//end namespace bali
#endif
