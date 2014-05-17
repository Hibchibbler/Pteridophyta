#include "CompLogicLobby.h"

#include "Game.h"
#include "Stage.h"
#include "Context.h"
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
ReturnVal CompLogicLobby::initialize()
{
    //Subscribe to...

    return ReturnVal();
}

ReturnVal CompLogicLobby::doRemoteEvent(CommEvent & event)
{
    Context& ctx = stage->game->ctx;
    uint32_t msgId;
    Player::Ptr p = ctx.mp.getPlayerByCid(event.connectionId);
    if (p != nullptr){
        //p is a nullptr if on client
    }
    (*event.packet) >> msgId;
    switch (msgId){
    //Client side
    case Messages::MsgId::WhoIsAck:{
            std::cout << "Got WhoIsAck" << std::endl;
            Command::Argument::Ptr  arg = CommandComponent::structifyWhoIsAck(event);
            Command::Ptr            cmd = std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSWHOISACKMSG, arg);
            stage->submitToComponents(cmd);
            break;
    }
    case Messages::MsgId::IdAck:{
            std::cout << "Got IdAck, " ;
            Command::Argument::Ptr  arg = CommandComponent::structifyIdAck(event);
            Command::Ptr            cmd = std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSIDACKMSG, arg);
            stage->submitToComponents(cmd);
            break;
    }
    case Messages::MsgId::IdNack:{
            std::cout << "Got IdNack" << std::endl;
            Command::Ptr            cmd = std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSIDNACKMSG, nullptr);
            stage->submitToComponents(cmd);
            break;
    }
    case Messages::MsgId::Start:{
            std::cout << "Got Start" << std::endl;
            Command::Ptr            cmd = std::make_shared<CommandComponent>(CommandComponent::Functions::PROCESSSTARTMSG, nullptr);
            stage->submitToComponents(cmd);

            Command::Ptr           cmd2 = std::make_shared<CommandStage>(CommandStage::Functions::STAGEFINISH, nullptr);
            stage->submitCommand(cmd2);
            break;
        }

    //Server Side
    case Messages::MsgId::WhoIs:{
            std::cout << "Got WhoIs" << std::endl;
            Messages::sendWhoIsAck(ctx.net, p, ctx.mp);
            break;
        }case Messages::MsgId::Id:{
            std::cout << "Got Id" << std::endl;
            (*event.packet) >> p->name;
            (*event.packet) >> p->team;

            p->setIdentity();

            Messages::sendIdAck(ctx.net, p, ctx.mp, ctx.mc);
            //Messages::sendIdNack(gs->net, p);
            break;
        }case Messages::MsgId::Ready:{
            std::cout << "Got Ready" << std::endl;
            p->setReady();

            const uint32_t MINPLAYERS = 1;
            if (ctx.mp.getNumPlayers() >= MINPLAYERS && ctx.mp.isAllPlayersReady())
            {
                Messages::sendStart(ctx.net);
            }
            break;
        }
    }
    return ReturnVal();
}

ReturnVal CompLogicLobby::doWindowEvent(sf::Event & event)
{
    return ReturnVal();
}

ReturnVal CompLogicLobby::doLocalInputs()
{
    return ReturnVal();
}

ReturnVal CompLogicLobby::doUpdate()
{
    return ReturnVal();
}

ReturnVal CompLogicLobby::doDraw()
{
    return ReturnVal();
}

ReturnVal CompLogicLobby::cleanup()
{
    return ReturnVal();
}

uint32_t CompLogicLobby::processCommands(void* arg)
{
    return 0;
}

}
