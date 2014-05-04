#ifndef CompLobbyWindow_h_
#define CompLobbyWindow_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"

#define PLAYER_SLOTS 5

namespace bali
{
class ContextClient;
class CompWindowLobby : public Component
{
public:
    CompWindowLobby(Stage* stage);
    ~CompWindowLobby();

    //General Component Functionality
    uint32_t initialize(Context& cc);
    uint32_t doWindowEvent(Context& cc, sf::Event & event);
    uint32_t doLocalInputs(Context& cc);
    uint32_t doUpdate(Context& cc);
    uint32_t doDraw(Context& cc);
    uint32_t cleanup(Context& cc);
    uint32_t processCommands(void* arg);
    uint32_t isCommandSupported(uint32_t function)
    {
        if ((CommandComponent::Functions)function == CommandComponent::Functions::PROCESSIDNACKMSG ||
            (CommandComponent::Functions)function == CommandComponent::Functions::PROCESSIDACKMSG ||
            (CommandComponent::Functions)function == CommandComponent::Functions::PROCESSWHOISACKMSG )
            return 1;
        return 0;
    }

    //Specific Component Functionality
    void doReady(ContextClient* cc);
    uint32_t isReady();

    void clearNames();
    void addName(std::string name);

    void handleIdAck(ContextClient& cc, CommandComponent::IdAckStruct & arg);
    void handleIdNack(ContextClient& cc);
    void handleWhoIsAck(ContextClient& cc, CommandComponent::WhoIsAckStruct & arg);


    std::vector<sfg::Entry::Ptr>     teamNameEntries;

    sfg::Window::Ptr    mywindow;//Kept to Show/Hide
    sfg::Box::Ptr       boxNames;
    sfg::Box::Ptr       boxMainVert;//kept to add the spinner later.
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

