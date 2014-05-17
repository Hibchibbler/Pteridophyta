#ifndef CompLobbyWindow_h_
#define CompLobbyWindow_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"

#define PLAYER_SLOTS 5

namespace bali
{
class Context;
class CompWindowLobby : public Component
{
public:
    CompWindowLobby(Stage* stage);
    ~CompWindowLobby();

    //General Component Functionality
    ReturnVal initialize();
    ReturnVal doWindowEvent(sf::Event & event);
    ReturnVal doLocalInputs();
    ReturnVal doUpdate();
    ReturnVal doDraw();
    ReturnVal cleanup();
    uint32_t  processCommands(void* arg);


    //Specific Component Functionality
    void doReady(Context* ctx);
    uint32_t isReady();

    void clearNames();
    void addName(std::string name);

    void handleIdAck(Context& ctx, CommandComponent::IdAckStruct & arg);
    void handleIdNack(Context& ctx);
    void handleWhoIsAck(Context& ctx, CommandComponent::WhoIsAckStruct & arg);


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
    void doJoinTeam(Context* ctx);

    sfg::Window::Ptr        window;
    sfg::Desktop            desk;
    uint32_t                ready=0;
};

}//end namespace bali

#endif

