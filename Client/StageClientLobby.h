#ifndef StageClientLobby_h_
#define StageClientLobby_h_

#include "GameStage.h"
#include <SFGUI\SFGUI.hpp>
#include "CompLobbyWindow.h"

namespace bali{
    class StageClientLobby : public GameStage
    {

    public:
        StageClientLobby(Game* game, uint32_t uid);
        ~StageClientLobby();

        uint32_t initialize();
        uint32_t doRemoteEvent(CommEvent & event);
        uint32_t doWindowEvents(sf::Event & event);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();
    private:
//        sfg::Entry::Ptr     team1[5];
//        sfg::Entry::Ptr     team2[5];
//        sfg::Window::Ptr    mywindow;//Kept to Show/Hide
//        sfg::Box::Ptr       box;//kept to add the spinner later.
//        sfg::Button::Ptr    joinTeam1Button;//kept to hide later.
//        sfg::Button::Ptr    joinTeam2Button;//kept to hide later.
//        sfg::Spinner::Ptr   spinner;
//        sfg::Label::Ptr     msg;
//        sfg::Button::Ptr    readyButton;

        sf::Clock           sendWhoIsClk;

//        static void doJoinTeam1(StageClientLobby* l);
//        static void doJoinTeam2(StageClientLobby* l);
//        static void doReady(StageClientLobby* l);

        CompLobbyWindow compLobbyWindow;

    };
}//end namespace bali
#endif
