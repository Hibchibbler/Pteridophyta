#include "CompLogicLobby.h"
#include "Stage.h"
#include "Messages.h"
#include <iostream>
namespace bali{

CompLogicLobby::CompLogicLobby(Stage* stage)
    : Component(stage)
{
}

CompLogicLobby::~CompLogicLobby()
{
}

//General Component Functionality
uint32_t CompLogicLobby::initialize(Context& cc)
{

    //Subscribe to...
    stage->subscribe(CommandComponent::Functions::PROCESSDATA, this);

    return 0;
}

uint32_t CompLogicLobby::doRemoteEvent(Context& cc, CommEvent & event)
{
    uint32_t msgId;
    (*event.packet) >> msgId;
    switch (msgId){
     case Messages::MsgId::WhoIsAck:{
            std::cout << "Got WhoIsAck" << std::endl;
            Command::Argument::Ptr  arg = CommandComponent::structifyWhoIsAck(event);
            Command::Ptr            cmd = std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSWHOISACKMSG, arg);
            stage->submitToComponents(cmd);
            break;
    }case Messages::MsgId::IdAck:{
            std::cout << "Got IdAck, " ;
            Command::Argument::Ptr  arg = CommandComponent::structifyIdAck(event);
            Command::Ptr            cmd = std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSIDACKMSG, arg);
            stage->submitToComponents(cmd);
            break;
    }case Messages::MsgId::IdNack:{
            std::cout << "Got IdNack" << std::endl;
            Command::Ptr            cmd = std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSIDNACKMSG, nullptr);
            stage->submitToComponents(cmd);
            break;
    }case Messages::MsgId::Start:{
            std::cout << "Got Start" << std::endl;
            Command::Ptr            cmd = std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSSTARTMSG, nullptr);
            stage->submitToComponents(cmd);

            Command::Ptr           cmd2 = std::make_shared<CommandStage>(CommandStage::Functions::STAGEFINISH, nullptr);
            stage->submitCommand(cmd2);
            break;
        }
    }

    return 0;
}

uint32_t CompLogicLobby::doWindowEvent(Context& cc, sf::Event & event)
{
    return 0;
}

uint32_t CompLogicLobby::doLocalInputs(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::doUpdate(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::doDraw(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::cleanup(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::processCommands(void* arg)
{
    return 0;
}

}
