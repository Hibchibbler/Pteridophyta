
#include "StageClientLobby.h"
#include "GameClient.h"
#include "Comm.h"
#include "Messages.h"
#include <SFGUI\SFGUI.hpp>
#include "Command.h"



namespace bali{

using namespace sfg;

StageClientLobby::StageClientLobby(Game* game, uint32_t uid)
    : Stage(game, uid)//, compWindowLobby(this)
{
}

StageClientLobby::~StageClientLobby()
{
}

uint32_t StageClientLobby::initialize()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    //Add Components
    compWindowLobby = std::make_shared<CompWindowLobby>(this);
    components.push_back(compWindowLobby);

    //compWindowLobby ->initialize(cc);
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
    //compWindowLobby->doWindowEvent(cc, event);
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
            submitToComponents(CommandComponent(CommandComponent::Functions::PROCESSWHOISACKMSG);
            break;
    }case MsgId::IdAck:{
            std::cout << "Got IdAck, " ;
            submitToComponents(CommandComponent(CommandComponent::Functions::PROCESSIDACKMSG);
            break;
    }case MsgId::IdNack:{
            std::cout << "Got IdNack" << std::endl;
            submitToComponents(CommandComponent(CommandComponent::Functions::PROCESSIDNACKMSG);
            submitCommand(CommandStage(CommandStage::Functions::SENDWHOIS));
            break;
    }case MsgId::Start:{
            std::cout << "Got Start" << std::endl;
            submitToComponents(CommandComponent(CommandComponent::Functions::PROCESSSTARTMSG);
            submitCommand(CommandStage(CommandStage::Functions::STAGEFINISH));
            break;
        }
    }

    return 0;
}
uint32_t StageClientLobby::processCommands(void* arg)
{
    ContextClient& cc = (GET_CLIENT_CONTEXT(g));

    for (auto& c : commands)
    {
        switch (c.getFunction())
        {
            case CommandStage::Functions::STAGEFINISH:
                std::cout << "Processing STAGEFINISH" << std::endl;
                finished(0);
                break;
            case CommandStage::Functions::SENDWHOIS:
                Messages::sendWhoIs(cc.net, cc.mp.player);
                break;
            case CommandStage::Functions::SENDID:
                Messages::sendId(cc.net, cc.mp.player);
                break;
            case CommandStage::Functions::SENDREADY:
                Messages::sendReady(cc.net, cc.mp.player);

                //
                //The player is ready when we recieve Ready from client.
                //And player is identified.
                //
                if (cc.mp.player.isIdentified())
                    cc.mp.player.setReady();
                else
                    std::cout << "Ready received, but not identified yet." << std::endl;

                break;
        }
    }

    commands.clear();
    return 0;
}

uint32_t StageClientLobby::doUpdate()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    //Process Queued Stage Commands
    processCommands(nullptr);

    //Process Queued Local Player Commands
    //cc.mp.processLocalCommands();

    //Send WhoIs every 1 seconds to update lobby lists
    if (sendWhoIsClk.getElapsedTime().asSeconds() > 1)
    {
        submitCommand(CommandStage(CommandStage::Functions::WHOIS));
        sendWhoIsClk.restart();
    }


    compWindowLobby->doUpdate(cc);


//    if (compLobbyWindow.isReady())
//    {
//        finished(0);
//    }
    return 0;
}
uint32_t StageClientLobby::doLocalInputs()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    compWindowLobby->doLocalInputs(cc);

    return 0;
}


uint32_t StageClientLobby::doDraw()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    cc.window.clear();
    cc.window.resetGLStates();

    compWindowLobby->doDraw(cc);

    cc.window.display();
    return 0;
}

uint32_t StageClientLobby::cleanup()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    compWindowLobby->cleanup(cc);

    return 0;
}

}//end namespace bali
