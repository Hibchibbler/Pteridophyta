#ifndef CompLobbyWindow_h_
#define CompLobbyWindow_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"


namespace bali
{

class CompLobbyWindow : public Component
{
public:
    CompLobbyWindow();
    ~CompLobbyWindow();
    uint32_t initialize(ContextClient& cc);
    uint32_t doWindowEvents(ContextClient& cc, sf::Event & event);
    uint32_t doLocalInputs(ContextClient& cc);
    uint32_t doUpdate(ContextClient& cc);
    uint32_t doDraw(ContextClient& cc);
    uint32_t cleanup(ContextClient& cc);
    void doReady(ContextClient* cc);
    uint32_t isReady();

    sfg::Entry::Ptr     team1[5];
    sfg::Entry::Ptr     team2[5];

    sfg::Window::Ptr    mywindow;//Kept to Show/Hide
    sfg::Box::Ptr       box;//kept to add the spinner later.
    sfg::Button::Ptr    joinTeam1Button;//kept to hide later.
    sfg::Button::Ptr    joinTeam2Button;//kept to hide later.
    sfg::Spinner::Ptr   spinner;
    sfg::Label::Ptr     msg;
    sfg::Button::Ptr    readyButton;

    sf::Clock           deskUpdateClock;
    sf::Clock           sendWhoIsClk;
private:
    void doJoinTeam1(ContextClient* cc);
    void doJoinTeam2(ContextClient* cc);

    sfg::Window::Ptr        window;
    sfg::Desktop            desk;
    uint32_t                ready=0;
};

}//end namespace bali

#endif

