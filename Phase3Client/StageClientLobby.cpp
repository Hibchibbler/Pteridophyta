
#include "StageClientLobby.h"
#include "GameClient.h"
#include "Comm.h"
#include "Messages.h"
#include <SFGUI\SFGUI.hpp>



namespace bali{

StageClientLobby::StageClientLobby(Game & game, sf::Uint32 uid)
    : GameStage(game, uid)
{

}

StageClientLobby::~StageClientLobby()
{

}
sf::Uint32 StageClientLobby::initialize()
{
    ContextClient *ctx = ((ContextClient*)(g.gameContext));
    GameClient* gc = ((GameClient*)&g);

    gc->client.StartClient(5676,sf::IpAddress("192.168.1.13"));
    sf::sleep(sf::seconds(3));
    std::cout << "Hi from StageClientLobby::initialize() =>" << std::endl;
    std::cout << ctx->name << ", "
              << ctx->pass << ", "
              << ctx->port << ", "
              << ctx->ip << std::endl;

    box =  sfg::Box::Create( sfg::Box::VERTICAL, 5.0f );

    sfg::Box::Ptr row = sfg::Box::Create( sfg::Box::HORIZONTAL, 5.0f );
    row->Pack(sfg::Label::Create("Team 1"));
    row->Pack(sfg::Label::Create("Team 2"));
    box->Pack(row);

    for (int i = 0;i < 5;i++){
        row = sfg::Box::Create( sfg::Box::HORIZONTAL, 5.0f );
        team1[i] = sfg::Entry::Create("");
        row->Pack(team1[i],true,true);
        team2[i] = sfg::Entry::Create("");
        row->Pack(team2[i],true,true);
        box->Pack(row);
    }

    row = sfg::Box::Create( sfg::Box::HORIZONTAL, 5.0f );

    joinTeam1Button = sfg::Button::Create("Join Team 1");
    joinTeam1Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StageClientLobby::doJoinTeam1, this );
    row->Pack(joinTeam1Button);

    joinTeam2Button = sfg::Button::Create("Join Team 2");
    joinTeam2Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StageClientLobby::doJoinTeam2, this );
    row->Pack(joinTeam2Button);
    box->Pack(row);

    row = sfg::Box::Create(sfg::Box::HORIZONTAL, 10.0f);
    spinner = sfg::Spinner::Create();
    spinner->Show(false);
    msg = sfg::Label::Create("Waiting for Host to start...");
    msg->Show(false);
    row->Pack(spinner);
    row->Pack(msg);
    box->Pack(row);
    //joinButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StageStart::doJoin, this );

    mywindow = sfg::Window::Create();
    mywindow->SetTitle("Lobby");
    mywindow->SetPosition(sf::Vector2f(100.0f,100.0f));
    mywindow->Add(box);

    gc->desk.Add(mywindow);



    initialized();
    return 0;
}

//sfg::Window::Ptr createNameDialog();
void StageClientLobby::doJoinTeam1()
{
    GameClient* gc = ((GameClient*)&g);
    ContextClient* cc = ((ContextClient*)(g.gameContext));

    //Send Id
    cc->team = 1;
    gc->mp.player.team = cc->team;
    gc->mp.player.stateClient = StatePlayerClient::SendId;

    joinTeam1Button->Show(false);
    joinTeam2Button->Show(false);

    spinner->Show(true);
    spinner->Start();
    msg->Show(true);
}

void StageClientLobby::doJoinTeam2()
{
    GameClient* gc = ((GameClient*)&g);
    ContextClient* cc = ((ContextClient*)(g.gameContext));

    //Send Id
    cc->team = 2;
    gc->mp.player.team = cc->team;
    gc->mp.player.stateClient = StatePlayerClient::SendId;

    joinTeam1Button->Show(false);
    joinTeam2Button->Show(false);

    spinner->Show(true);
    spinner->Start();
    msg->Show(true);
}


sf::Uint32 StageClientLobby::doWindowEvents(sf::Event & event)
{
    GameClient* gc = ((GameClient*)&g);
    gc->desk.HandleEvent(event);
    return 0;
}

sf::Uint32 StageClientLobby::doRemoteEvents(CommEvent & cevent)
{
    GameClient* gc = ((GameClient*)&g);
    sf::Uint32 msgId;
    cevent.packet >> msgId;

    switch (msgId){
     case MsgId::WhoIsAck:{
            std::cout << "Got WhoIsAck" << std::endl;
            gc->mp.player.stateClient = StatePlayerClient::Waiting;
            break;
    }case MsgId::IdAck:{
            std::cout << "Got IdAck" << std::endl;//mySlot <<   std::endl;
            gc->mp.player.stateClient = StatePlayerClient::Waiting;
            break;
    }case MsgId::IdNack:{
            std::cout << "Got IdNack" << std::endl;
            gc->mp.player.stateClient = StatePlayerClient::SendWhoIs;

            joinTeam1Button->Show(true);
            joinTeam2Button->Show(true);
            spinner->Show(false);
            spinner->Stop();
            msg->Show(false);
            break;
    }case MsgId::Start:{
            std::cout << "Got Start" << std::endl;
            gc->mp.player.stateClient = StatePlayerClient::Established;
            finished(0);
            break;
        }
    }
    return 0;
}



sf::Uint32 StageClientLobby::doLoop()
{
    GameClient* gc = ((GameClient*)&g);

    gc->desk.Update(1);
    sf::Uint32 s = gc->mp.player.stateClient;

    switch (s){
        case StatePlayerClient::Waiting:
            //Waiting for some reply.
            break;
        case StatePlayerClient::SendWhoIs:
            //std::cout << "Sent WhoIs." << std::endl;
            Messages::sendWhoIs(gc->client, gc->mp.player);
            s = StatePlayerClient::Waiting;//WaitWhoIsAck;
            break;
        case StatePlayerClient::SendId:{
            //std::cout << "Sent Id." << std::endl;
            Messages::sendId(gc->client, gc->mp.player);
            s = StatePlayerClient::Waiting;//WaitIdAck;
            break;
        }
        case StatePlayerClient::SendReady:
            //std::cout << "Sent Ready." << std::endl;
            Messages::sendReady(gc->client, gc->mp.player);
            s = StatePlayerClient::Waiting;//WaitStart;
            break;
    }
    gc->mp.player.stateClient = s;

    return 0;
}
sf::Uint32 StageClientLobby::doLocalInputs()
{
    return 0;
}


sf::Uint32 StageClientLobby::doDraw()
{
    GameClient* gc = ((GameClient*)&g);

    gc->window.clear();
    gc->window.resetGLStates();

    gc->sfGui.Display(gc->window);
    gc->window.display();
    return 0;
}

sf::Uint32 StageClientLobby::cleanup()
{

    return 0;
}

}//end namespace bali
