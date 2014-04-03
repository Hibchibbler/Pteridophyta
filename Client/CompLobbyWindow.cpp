
#include "CompLobbyWindow.h"
#include "ContextClient.h"


namespace bali{

CompLobbyWindow::CompLobbyWindow()
{
}

CompLobbyWindow::~CompLobbyWindow()
{
}

uint32_t CompLobbyWindow::initialize(ContextClient& cc)
{

    cc.net.startClient(5676,sf::IpAddress("192.168.1.13"));
    //sf::sleep(sf::seconds(6));
    std::cout << "CompLobbyWindow::initialize()" << ", "
              << cc.mp.player.name << ", "
              << cc.mp.player.pass << ", "
              << cc.mp.player.server_port << ", "
              << cc.mp.player.server_ip << std::endl;


    box =  sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );

    sfg::Box::Ptr row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.0f );
    row->Pack(sfg::Label::Create("Team 1"));
    row->Pack(sfg::Label::Create("Team 2"));
    box->Pack(row);

    for (int i = 0;i < 5;i++){
        row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.0f );
        team1[i] = sfg::Entry::Create("");
        row->Pack(team1[i],true,true);
        team2[i] = sfg::Entry::Create("");
        row->Pack(team2[i],true,true);
        box->Pack(row);
    }

    row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.0f );

    joinTeam1Button = sfg::Button::Create("Join Team 1");
    joinTeam1Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&CompLobbyWindow::doJoinTeam1, this, &cc) );
    row->Pack(joinTeam1Button);

    joinTeam2Button = sfg::Button::Create("Join Team 2");
    joinTeam2Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&CompLobbyWindow::doJoinTeam2, this, &cc) );
    row->Pack(joinTeam2Button);
    box->Pack(row);

    row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 10.0f );
    readyButton = sfg::Button::Create("Ready");
    readyButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&CompLobbyWindow::doReady, this, &cc) );
    readyButton->Show(false);//Don't show until team is joined.
    row->Pack(readyButton);
    box->Pack(row);

    row = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.0f);
    spinner = sfg::Spinner::Create();
    spinner->Show(false);
    msg = sfg::Label::Create("Waiting for Host to start...");
    msg->Show(false);
    row->Pack(spinner);
    row->Pack(msg);
    box->Pack(row);

    window = sfg::Window::Create();
    window->SetTitle("Lobby");
    window->SetPosition(sf::Vector2f(100.0f,100.0f));
    window->Add(box);

    desk.Add(window);

    return 0;
}
uint32_t CompLobbyWindow::doWindowEvents(ContextClient& cc, sf::Event & event)
{
    desk.HandleEvent(event);
    return 0;
}

uint32_t CompLobbyWindow::doLocalInputs(ContextClient& cc)
{
    return 0;
}
uint32_t CompLobbyWindow::doUpdate(ContextClient& cc)
{
    desk.Update(deskUpdateClock.restart().asSeconds());
    return 0;
}

uint32_t CompLobbyWindow::doDraw(ContextClient& cc)
{
    cc.sfGui.Display(cc.window);
    return 0;
}

uint32_t CompLobbyWindow::cleanup(ContextClient& cc)
{
    return 0;
}

void CompLobbyWindow::doReady(ContextClient* cc)
{
    cc->mp.player.setReady();
    cc->mp.player.stateClient = StatePlayerClient::SendReady;
    readyButton->Show(false);
    ready=1;
}

uint32_t CompLobbyWindow::isReady(){
    return ready;
}


void CompLobbyWindow::doJoinTeam1(ContextClient* cc)
{
    //Send Id - declare team 1
    cc->mp.player.team = 1;
    cc->mp.player.stateClient = StatePlayerClient::SendId;

    joinTeam1Button->Show(false);
    joinTeam2Button->Show(false);

    spinner->Show(true);
    spinner->Start();
    msg->Show(true);
}

void CompLobbyWindow::doJoinTeam2(ContextClient* cc)
{
    //Send Id - declare team 2
    cc->mp.player.team = 2;
    cc->mp.player.stateClient = StatePlayerClient::SendId;

    joinTeam1Button->Show(false);
    joinTeam2Button->Show(false);

    spinner->Show(true);
    spinner->Start();
    msg->Show(true);

}

}//end namespace bali
