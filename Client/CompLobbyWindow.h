#ifndef CompLobbyWindow_h_
#define CompLobbyWindow_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"


namespace bali
{
class ContextClient;
class CompLobbyWindow : public Component
{
public:
    CompLobbyWindow();
    ~CompLobbyWindow();

    //General Component Functionality
    uint32_t initialize(Context& cc);
    uint32_t doWindowEvent(Context& cc, sf::Event & event);
    uint32_t doLocalInputs(Context& cc);
    uint32_t doUpdate(Context& cc);
    uint32_t doDraw(Context& cc);
    uint32_t cleanup(Context& cc);

    //Specific Component Functionality
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

