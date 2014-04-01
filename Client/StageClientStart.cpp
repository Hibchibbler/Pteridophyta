#include "StageClientStart.h"
#include "GameClient.h"
#include <iostream>

namespace bali{

StageClientStart::StageClientStart(Game* game, uint32_t uid)
 :  GameStage(game, uid)
{


}

StageClientStart::~StageClientStart()
{

}

void StageClientStart::doStart()
{
    std::string name = nameEntry->GetText();
    std::string pass = passEntry->GetText();
    std::string port = portEntry->GetText();
    std::string ip   = ipEntry->GetText();
    std::cout << "Hi " << name << std::endl;

    ContextClient* cc = GET_CLIENT_CONTEXT(g);
    cc->mp.player.name = name;
    cc->mp.player.pass = pass;
    cc->mp.player.server_port = atoi(port.c_str());
    cc->mp.player.server_ip = ip;

    setupWindow->Show(false);

    finished(0);
}
uint32_t StageClientStart::initialize()
{

    //Construct Start Menu GUI
    sfg::Table::Ptr table( sfg::Table::Create(  ) );

    sfg::Label::Ptr nameLabel;
    nameLabel = sfg::Label::Create("Name");
    nameEntry = sfg::Entry::Create();
    nameEntry->SetRequisition(sf::Vector2f(120.0f,0.0f));
    table->Attach(nameLabel,sf::Rect<sf::Uint32>(0,0,1,1), 0);
    table->Attach(nameEntry,sf::Rect<sf::Uint32>(1,0,1,1), 3);

    sfg::Label::Ptr passLabel;
    passLabel = sfg::Label::Create("Password");
    passEntry = sfg::Entry::Create();
    table->Attach(passLabel, sf::Rect<sf::Uint32>(0,1,1,1), 0);
    table->Attach(passEntry, sf::Rect<sf::Uint32>(1,1,1,1), 3);

    sfg::Label::Ptr ipLabel;
    ipLabel = sfg::Label::Create("IP");
    ipEntry = sfg::Entry::Create();
    table->Attach(ipLabel, sf::Rect<sf::Uint32>(0,2,1,1), 0);
    table->Attach(ipEntry, sf::Rect<sf::Uint32>(1,2,1,1), 3);

    sfg::Label::Ptr portLabel;
    portLabel = sfg::Label::Create("Port");
    portEntry = sfg::Entry::Create();
    table->Attach(portLabel, sf::Rect<sf::Uint32>(0,3,1,1), 0);
    table->Attach(portEntry, sf::Rect<sf::Uint32>(1,3,1,1), 3);


    sfg::Button::Ptr startButton;
    startButton = sfg::Button::Create("Start");
    startButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&StageClientStart::doStart, this) );
    table->Attach(startButton, sf::Rect<sf::Uint32>(0,4,2,1), 3);


    setupWindow = sfg::Window::Create();

    setupWindow->SetTitle("Phase 3");
    setupWindow->SetRequisition(sf::Vector2f(425,300));
    setupWindow->SetPosition(sf::Vector2f(100.0f,100.0f));
    setupWindow->Add(table);

    setupDesktop.Add(setupWindow);


    //Set this so Game knows we are initialized, so it won't
    // initialize us again.
    initialized();
    return 0;
}

uint32_t StageClientStart::doRemoteEvent(CommEvent & event)
{
    return 0;
}

uint32_t StageClientStart::doWindowEvents(sf::Event & wevent)
{
    setupDesktop.HandleEvent(wevent);
    return 0;
}
uint32_t StageClientStart::doLocalInputs()
{
    return 0;
}

uint32_t StageClientStart::doUpdate()
{
    setupDesktop.Update(1.0f);
    return 0;
}
uint32_t StageClientStart::doDraw()
{
    ContextClient* cc = GET_CLIENT_CONTEXT(g);
    cc->window.clear();
    cc->window.resetGLStates();
    cc->sfGui.Display(cc->window);
    cc->window.display();
    return 0;
}
uint32_t StageClientStart::cleanup()
{

    return 0;
}


}//end namespace bali
