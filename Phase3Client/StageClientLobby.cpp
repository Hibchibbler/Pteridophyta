
#include "StageClientLobby.h"
#include "GameClient.h"
#include "Comm.h"
#include "Messages.h"
#include <SFGUI\SFGUI.hpp>



namespace bali{

using namespace sfg;

StageClientLobby::StageClientLobby(Game & game, uint32_t uid)
    : GameStage(game, uid)
{

}

StageClientLobby::~StageClientLobby()
{

}
uint32_t StageClientLobby::initialize()
{
    ContextClient *ctx = ((ContextClient*)(g.gameContext));
    GameClient* gc = ((GameClient*)&g);



    gc->client.startClient(5676,sf::IpAddress("192.168.1.13"));
    //sf::sleep(sf::seconds(6));
    std::cout << "Hi from StageClientLobby::initialize() =>" << std::endl;
    std::cout << ctx->name << ", "
              << ctx->pass << ", "
              << ctx->port << ", "
              << ctx->ip << std::endl;

    gc->mp.player.name = ctx->name;


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
    joinTeam1Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(StageClientLobby::doJoinTeam1, this) );
    row->Pack(joinTeam1Button);

    joinTeam2Button = sfg::Button::Create("Join Team 2");
    joinTeam2Button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(StageClientLobby::doJoinTeam2, this) );
    row->Pack(joinTeam2Button);
    box->Pack(row);

    row = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 10.0f );
    readyButton = sfg::Button::Create("Ready");
    readyButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(StageClientLobby::doReady, this) );
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
    //joinButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &StageStart::doJoin, this );

    mywindow = sfg::Window::Create();
    mywindow->SetTitle("Lobby");
    mywindow->SetPosition(sf::Vector2f(100.0f,100.0f));
    mywindow->Add(box);

    gc->desk.Add(mywindow);



    initialized();
    return 0;
}

void StageClientLobby::doReady(StageClientLobby* l)
{
    GameClient* gc = ((GameClient*)&l->g);
    //ContextClient* cc = ((ContextClient*)(gc->gameContext));

    gc->mp.player.setReady();
    gc->mp.player.stateClient = StatePlayerClient::SendReady;
    l->readyButton->Show(false);

}

//sfg::Window::Ptr createNameDialog();
void StageClientLobby::doJoinTeam1(StageClientLobby* l)
{
    GameClient* gc = ((GameClient*)&l->g);
    ContextClient* cc = ((ContextClient*)(gc->gameContext));

    //Send Id
    cc->team = 1;
    gc->mp.player.team = cc->team;
    gc->mp.player.stateClient = StatePlayerClient::SendId;

    l->joinTeam1Button->Show(false);
    l->joinTeam2Button->Show(false);


    l->spinner->Show(true);
    l->spinner->Start();
    l->msg->Show(true);
}

void StageClientLobby::doJoinTeam2(StageClientLobby* l)
{
    GameClient* gc = ((GameClient*)&l->g);
    ContextClient* cc = ((ContextClient*)(gc->gameContext));

    //Send Id
    cc->team = 2;
    gc->mp.player.team = cc->team;
    gc->mp.player.stateClient = StatePlayerClient::SendId;

    l->joinTeam1Button->Show(false);
    l->joinTeam2Button->Show(false);

    l->spinner->Show(true);
    l->spinner->Start();
    l->msg->Show(true);

}


uint32_t StageClientLobby::doWindowEvents(sf::Event & event)
{
    GameClient* gc = ((GameClient*)&g);
    gc->desk.HandleEvent(event);
    return 0;
}

uint32_t StageClientLobby::doRemoteEvents(CommEvent & event)
{
    GameClient* gc = ((GameClient*)&g);
    uint32_t msgId;
    (*event.packet) >> msgId;

    switch (msgId){
     case MsgId::WhoIsAck:{
            std::cout << "Got WhoIsAck" << std::endl;
            gc->mp.player.stateClient = StatePlayerClient::Waiting;
            uint32_t t1o=0;
            uint32_t t2o=0;

            uint32_t np;
            (*event.packet) >> np;

            //Clear all the slots, in preparation for update.
            for (int i = 0;i < 5;i++)
            {
                team1[i]->SetText(sf::String(""));
                team2[i]->SetText(sf::String(""));
            }

            for (int i = 0;i < np;i++)
            {
                std::string name;
                uint32_t team;
                (*event.packet) >> name >> team;
                if (team == 1)
                {
                    std::cout << "Adding " << name << " to team 1" << std::endl;
                    team1[t1o]->SetText(sf::String(name));
                    t1o++;
                }else
                {
                    std::cout << "Adding " << name << " to team 2" << std::endl;
                    team2[t2o]->SetText(sf::String(name));
                    t2o++;
                }
            }

            break;
    }case MsgId::IdAck:{
            std::cout << "Got IdAck" << std::endl;
            readyButton->Show(true);
            gc->mp.player.setIdentity();
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



uint32_t StageClientLobby::doLoop()
{
    GameClient* gc = ((GameClient*)&g);

    gc->desk.Update(1);
    uint32_t s = gc->mp.player.stateClient;

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

            //
            //The player is ready when we recieve Ready from client.
            //And player is identified.
            //
            if (gc->mp.player.isIdentified())
                gc->mp.player.setReady();
            else
                std::cout << "Ready received, but not identified yet." << std::endl;

            s = StatePlayerClient::Waiting;//WaitStart;
            break;
    }
    gc->mp.player.stateClient = s;

    //Send WhoIs every 2 seconds to update lobby lists
    if (sendWhoIsClk.getElapsedTime().asSeconds() > 1)
    {
        gc->mp.player.stateClient = StatePlayerClient::SendWhoIs;
        sendWhoIsClk.restart();
    }
    return 0;
}
uint32_t StageClientLobby::doLocalInputs()
{
    return 0;
}


uint32_t StageClientLobby::doDraw()
{
    GameClient* gc = ((GameClient*)&g);

    gc->window.clear();
    gc->window.resetGLStates();

    gc->sfGui.Display(gc->window);
    gc->window.display();
    return 0;
}

uint32_t StageClientLobby::cleanup()
{

    return 0;
}

}//end namespace bali
