
#include "StageClientLobby.h"
#include "GameClient.h"
#include "Comm.h"
#include "Messages.h"
#include <SFGUI\SFGUI.hpp>
#include "Command.h"



namespace bali{

using namespace sfg;

StageClientLobby::StageClientLobby(Game* game, uint32_t uid)
    : Stage(game, uid)//, compLobbyWindow(this)
{
}

StageClientLobby::~StageClientLobby()
{
}

uint32_t StageClientLobby::initialize()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    //Add Components
    components.push_back(std::make_shared<CompWindowLobby>(this));

    //Initialize components
    for (auto& c : components)
    {
        c->initialize(cc);
    }
    initialized();
    return 0;
}

uint32_t StageClientLobby::doWindowEvent(sf::Event & event)
{
    ContextClient& cc = (GET_CLIENT_CONTEXT(g));
    for (auto& c : components)
    {
        c->doWindowEvent(cc, event);
    }
    return 0;
}

uint32_t StageClientLobby::doRemoteEvent(CommEvent & event)
{
    ContextClient& cc = (GET_CLIENT_CONTEXT(g));
    uint32_t msgId;
    (*event.packet) >> msgId;

    switch (msgId){
     case MsgId::WhoIsAck:{
            std::cout << "Got WhoIsAck" << std::endl;
            cc.mp.player.stateClient = StatePlayerClient::Waiting;
            uint32_t t1o=0;
            uint32_t t2o=0;

            //Get number of (name,team) we're gunna get.
            uint32_t np;
            (*event.packet) >> np;
            compLobbyWindow.clearNames();
            for (int i = 0;i < np;i++)
            {
                std::string name;
                uint32_t team;
                (*event.packet) >> name >> team;
                compLobbyWindow.addName(name);
            }


//            Messages::WhoIsAck  wia = Messages::parsePacket(event);
//
//            CmdComponent cmd;
//            cmd.setFunction(CmdComponent::Functions::POPULATETEAMLIST);
//            cmd.ptl.names = ;

            break;
    }case MsgId::IdAck:{
            std::cout << "Got IdAck, " ;
            cc.mp.player.stateClient = StatePlayerClient::Waiting;

            std::string mapName;
            (*event.packet) >> mapName;
            std::cout << "Map: " << mapName << std::endl;


            compLobbyWindow.gotIdAck(cc, mapName);



            break;
    }case MsgId::IdNack:{
            std::cout << "Got IdNack" << std::endl;
            cc.mp.player.stateClient = StatePlayerClient::SendWhoIs;

            compLobbyWindow.gotIdNack(cc);

            break;
    }case MsgId::Start:{
            std::cout << "Got Start" << std::endl;
            cc.mp.player.stateClient = StatePlayerClient::Established;

            finished(0);

            break;
        }
    }

    return 0;
}
uint32_t StageClientLobby::processCommands()
{
    for (auto& i : commands)
    {
        switch (i.getFunction())
        {
            case CommandStage::Functions::TRANSITION:
                std::cout << "Processing TRANSITION" << std::endl;
                finished(0);
                break;
        }
    }

    commands.clear();
    return 0;
}

uint32_t StageClientLobby::doUpdate()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    processCommands();

    uint32_t s = cc.mp.player.stateClient;

    switch (s){
        case StatePlayerClient::Waiting:
            //Waiting for some reply.
            break;
        case StatePlayerClient::SendWhoIs:
            Messages::sendWhoIs(cc.net, cc.mp.player);
            s = StatePlayerClient::Waiting;
            break;
        case StatePlayerClient::SendId:{
            Messages::sendId(cc.net, cc.mp.player);
            s = StatePlayerClient::Waiting;
            break;
        }
        case StatePlayerClient::SendReady:
            Messages::sendReady(cc.net, cc.mp.player);

            //
            //The player is ready when we recieve Ready from client.
            //And player is identified.
            //
            if (cc.mp.player.isIdentified())
                cc.mp.player.setReady();
            else
                std::cout << "Ready received, but not identified yet." << std::endl;

            s = StatePlayerClient::Waiting;
            break;
    }
    cc.mp.player.stateClient = s;

    //Send WhoIs every 1 seconds to update lobby lists
    if (sendWhoIsClk.getElapsedTime().asSeconds() > 1)
    {
        cc.mp.player.stateClient = StatePlayerClient::SendWhoIs;
        sendWhoIsClk.restart();
    }


    for (auto& c : components)
    {
        c->doUpdate(cc);
    }

//    if (compLobbyWindow.isReady())
//    {
//        finished(0);
//    }
    return 0;
}
uint32_t StageClientLobby::doLocalInputs()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    for (auto& c : components)
    {
        c->doLocalInputs(cc);
    }
    return 0;
}


uint32_t StageClientLobby::doDraw()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    cc.window.clear();
    cc.window.resetGLStates();
    for (auto& c : components)
    {
        c->doDraw(cc);
    }

    cc.window.display();
    return 0;
}

uint32_t StageClientLobby::cleanup()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    for (auto& c : components)
    {
        c->cleanup(cc);
    }
    return 0;
}

}//end namespace bali
