#include "StageServerLobby.h"
#include "Comm.h"
#include "ManagerPlayer.h"
#include "GameServer.h"
#include "Messages.h"
#include <iostream>


namespace bali{

StageServerLobby::StageServerLobby(Game* game, uint32_t uid)
    : Stage(game, uid)
{
}

StageServerLobby::~StageServerLobby()
{
}

uint32_t StageServerLobby::initialize()
{
    Context& ctx = g->ctx;
    initialized();
    return 0;
}

uint32_t StageServerLobby::doRemoteEvent(CommEvent & event)
{
    Context& ctx = g->ctx;

    uint32_t msgId;
    uint32_t cid;

    cid = event.connectionId;
    (*event.packet) >> msgId;

    Player::Ptr p = ctx.mp.getPlayerByCid(cid);
    if (p == nullptr){
        std::cout << "p == nullptr" << std::endl;
        //a player with cid does not exist
        return STAGE_SERVER_LOBBY_ERROR;
    }
    switch (msgId){
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
    return STAGE_SERVER_LOBBY_SUCCESS;
}

uint32_t StageServerLobby::doUpdate()
{
    Context& ctx = g->ctx;
    return 0;
}

uint32_t StageServerLobby::doWindowEvent(sf::Event & event)
{
    Context& ctx = g->ctx;
    return 0;
}

uint32_t StageServerLobby::doLocalInputs()
{
    Context& ctx = g->ctx;
    return 0;
}

uint32_t StageServerLobby::doDraw()
{
    Context& ctx = g->ctx;
    return 0;
}

uint32_t StageServerLobby::cleanup()
{
    Context& ctx = g->ctx;
    return 0;
}

uint32_t StageServerLobby::processCommands(void* arg)
{
    return 0;
}

}//end namespace bali



