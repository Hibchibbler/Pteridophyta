
#include "StageClientLobby.h"
#include "GameClient.h"
#include "Comm.h"
#include "Messages.h"
#include <SFGUI\SFGUI.hpp>
#include "Command.h"



namespace bali{

using namespace sfg;

StageClientLobby::StageClientLobby(Game* game, uint32_t uid)
    : Stage(game, uid)
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


    //Initialize Component Command Subscribers
    //Creates an empty vector for each command function
    subscribers[CommandComponent::Functions::PAUSE];
    subscribers[CommandComponent::Functions::RESUME];
    subscribers[CommandComponent::Functions::SHOW];
    subscribers[CommandComponent::Functions::HIDE];
    subscribers[CommandComponent::Functions::PROCESSIDNACKMSG];
    subscribers[CommandComponent::Functions::PROCESSIDACKMSG];
    subscribers[CommandComponent::Functions::PROCESSWHOISACKMSG];

    //Initialize all components.
    //they each will subscribe to some, all, or none of the functions initialized above..
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
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    uint32_t msgId;
    (*event.packet) >> msgId;
    switch (msgId){
     case MsgId::WhoIsAck:{
            std::cout << "Got WhoIsAck" << std::endl;
            Command::Arg arg = CommandComponent::structifyWhoIsAck(event);
            submitToComponents(std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSWHOISACKMSG, arg));
            break;
    }case MsgId::IdAck:{
            std::cout << "Got IdAck, " ;
            Command::Arg arg = CommandComponent::structifyIdAck(event);
            submitToComponents(std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSIDACKMSG, arg));
            break;
    }case MsgId::IdNack:{
            std::cout << "Got IdNack" << std::endl;
            submitToComponents(std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSIDNACKMSG, nullptr));
            break;
    }case MsgId::Start:{
            std::cout << "Got Start" << std::endl;
            submitToComponents(std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSSTARTMSG, nullptr));
            submitCommand(std::make_shared<CommandStage>(CommandStage::Functions::STAGEFINISH, nullptr));
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
        switch (c->getFunction())
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

    //Send WhoIs every 1 seconds to update lobby lists
    if (sendWhoIsClk.getElapsedTime().asSeconds() > 1)
    {
        submitCommand(std::make_shared<CommandStage>(CommandStage::Functions::SENDWHOIS, nullptr));
        sendWhoIsClk.restart();
    }

    for (auto& c : components)
    {
        c->doUpdate(cc);
    }

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
