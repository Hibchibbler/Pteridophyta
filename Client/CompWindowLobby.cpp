
#include "CompWindowLobby.h"
#include "ContextClient.h"
#include "CommandStage.h"
#include "Stage.h"

namespace bali{

CompWindowLobby::CompWindowLobby(Stage* stage)
    : Component(stage)
{
}

CompWindowLobby::~CompWindowLobby()
{
}

uint32_t CompWindowLobby::initialize(Context& cc)
{

    cc.net.startClient(5676,sf::IpAddress("192.168.1.13"));
    //sf::sleep(sf::seconds(6));
    std::cout << "CompWindowLobby::initialize()" << ", "
              << cc.mp.player.name << ", "
              << cc.mp.player.pass << ", "
              << cc.mp.player.server_port << ", "
              << cc.mp.player.server_ip << std::endl;


    //Create Main Vertical Layout box
    boxMainVert =  sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );

    //Create Team Label, add to main box
    sfg::Box::Ptr row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.0f );
    row->Pack(sfg::Label::Create("The Team"));
    boxMainVert->Pack(row);

    //Create Name List Vertical Layout box as placeholder
    boxNames = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 10.0f );
    boxMainVert->Pack(boxNames);

    //Create Join Button Horiz Layout box, add to main box.
    //Add button, and connect button to function
    row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.0f );
    joinTeam1Button = sfg::Button::Create("Join The Team");
    joinTeam1Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&CompWindowLobby::doJoinTeam, this, (ContextClient*)&cc) );
    row->Pack(joinTeam1Button);
    boxMainVert->Pack(row);

    //Create Ready button Horiz layout box, add to main box
    //Add button, and connect button to function
    row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 10.0f );
    readyButton = sfg::Button::Create("Ready");
    readyButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&CompWindowLobby::doReady, this, (ContextClient*)&cc) );
    readyButton->Show(false);//Don't show until team is joined.
    row->Pack(readyButton);
    boxMainVert->Pack(row);

    //Create Spinner & Wait-Message Horiz layout box, add to main box
    //Add spinner, and wait message
    row = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.0f);
    spinner = sfg::Spinner::Create();
    spinner->Show(false);
    msg = sfg::Label::Create("Waiting for Host to start...");
    msg->Show(false);
    row->Pack(spinner);
    row->Pack(msg);
    boxMainVert->Pack(row);

    //Create Window
    //Add main box to window
    window = sfg::Window::Create();
    window->SetTitle("Lobby");
    window->SetPosition(sf::Vector2f(100.0f,100.0f));
    window->SetRequisition(sf::Vector2f(200,200));
    window->Add(boxMainVert);

    //Add window to desktop
    desk.Add(window);

    //Subscribe to...
    stage->subscribe(CommandComponent::Functions::PROCESSIDNACKMSG, this);
    stage->subscribe(CommandComponent::Functions::PROCESSIDACKMSG, this);
    stage->subscribe(CommandComponent::Functions::PROCESSWHOISACKMSG, this);
    return 0;
}
uint32_t CompWindowLobby::doWindowEvent(Context& cc, sf::Event & event)
{
    desk.HandleEvent(event);
    return 0;
}

uint32_t CompWindowLobby::doLocalInputs(Context& cc)
{
    return 0;
}

uint32_t CompWindowLobby::processCommands(void* arg)
{
    ContextClient* cc = (ContextClient*)arg;
    for (auto& c : commands)
    {
        switch (c->getFunction())
        {
            case CommandComponent::Functions::PROCESSIDNACKMSG:
                handleIdNack(*cc);
                break;
            case CommandComponent::Functions::PROCESSIDACKMSG:
                //handleIdAck(*cc, *((CommandComponent::IdAckStruct*)c->getArg()));
                handleIdAck(*cc, *std::static_pointer_cast<CommandComponent::IdAckStruct>(c->getArg()));
                break;
            case CommandComponent::Functions::PROCESSWHOISACKMSG:
                handleWhoIsAck(*cc,*std::static_pointer_cast<CommandComponent::WhoIsAckStruct>(c->getArg()));
                break;
        }
    }

    commands.clear();
    return 0;
}

uint32_t CompWindowLobby::doUpdate(Context& cc)
{
    processCommands(&cc);
    desk.Update(deskUpdateClock.restart().asSeconds());
    return 0;
}

uint32_t CompWindowLobby::doDraw(Context& c)
{
    ContextClient& cc = *((ContextClient*)&c);
    cc.sfGui.Display(cc.window);
    return 0;
}

uint32_t CompWindowLobby::cleanup(Context& cc)
{
    return 0;
}

void CompWindowLobby::doReady(ContextClient* cc)
{
    //cc->mp.player.setReady();
    //cc->mp.player.stateClient = StatePlayerClient::SendReady;
    stage->submitCommand(std::make_shared<CommandStage>(CommandStage::Functions::SENDREADY, nullptr));
    readyButton->Show(false);
    //ready=1;

    stage->submitCommand(std::make_shared<CommandStage>(CommandStage::Functions::STAGEFINISH, nullptr));
}

uint32_t CompWindowLobby::isReady(){
    return ready;
}

void CompWindowLobby::clearNames()
{
    boxNames->RemoveAll();
}

void CompWindowLobby::addName(std::string name)
{
    sfg::Box::Ptr row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.0f );
    row->Pack(sfg::Entry::Create(name),true,true);
    boxNames->Pack(row);
}


void CompWindowLobby::handleIdAck(ContextClient& cc, CommandComponent::IdAckStruct &arg)
{
//    std::string mapName;
//    (*event.packet) >> mapName;
    cc.mapName = arg.mapName;
    readyButton->Show(true);
    cc.mp.player.setIdentity();
}

void CompWindowLobby::handleIdNack(ContextClient& cc)
{
    joinTeam1Button->Show(true);
    spinner->Show(false);
    spinner->Stop();
    msg->Show(false);
}

void CompWindowLobby::handleWhoIsAck(ContextClient& cc, CommandComponent::WhoIsAckStruct &arg)
{
    clearNames();
    for (auto& n : arg.names)
    {
        addName(n.name);
    }

}

void CompWindowLobby::doJoinTeam(ContextClient* cc)
{

    stage->submitCommand(std::make_shared<CommandStage>(CommandStage::Functions::SENDID, nullptr));

    joinTeam1Button->Show(false);
    spinner->Show(true);
    spinner->Start();
    msg->Show(true);
}


}//end namespace bali
