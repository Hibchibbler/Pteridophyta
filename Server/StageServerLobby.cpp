#include "StageServerLobby.h"
#include "Comm.h"
#include "ManagerPlayer.h"
#include "GameServer.h"
#include "Messages.h"
#include <iostream>


namespace bali{

StageServerLobby::StageServerLobby(Game* game, uint32_t uid)
    : GameStage(game, uid)
{
}

StageServerLobby::~StageServerLobby()
{
}

uint32_t StageServerLobby::initialize()
{
    ContextServer& cs = GET_SERVER_CONTEXT(g);
    initialized();
    return 0;
}

uint32_t StageServerLobby::doRemoteEvent(CommEvent & event)
{
    ContextServer& cs = GET_SERVER_CONTEXT(g);

    uint32_t msgId;
    uint32_t cid;

    cid = event.connectionId;
    (*event.packet) >> msgId;

    SPlayer p = cs.mp.getPlayerByCid(cid);
    if (p == nullptr){
        std::cout << "p == nullptr" << std::endl;
        //a player with cid does not exist
        return STAGE_SERVER_LOBBY_ERROR;
    }
    switch (msgId){
        case MsgId::WhoIs:{
            std::cout << "Got WhoIs" << std::endl;
            Messages::sendWhoIsAck(cs.net, p, cs.mp);
            break;
        }case MsgId::Id:{
            std::cout << "Got Id" << std::endl;
            (*event.packet) >> p->name;
            (*event.packet) >> p->team;

            p->setIdentity();

            Messages::sendIdAck(cs.net, p, cs.mp, cs.mc);
            //Messages::sendIdNack(gs->net, p);
            break;
        }case MsgId::Ready:{
            std::cout << "Got Ready" << std::endl;
            p->setReady();

            const uint32_t MINPLAYERS = 1;
            if (cs.mp.getNumPlayers() >= MINPLAYERS && cs.mp.isAllPlayersReady())
            {
                Messages::sendStart(cs.net);
            }
            break;
        }
    }
    return STAGE_SERVER_LOBBY_SUCCESS;
}

uint32_t StageServerLobby::doUpdate()
{
    ContextServer& cs = GET_SERVER_CONTEXT(g);
    return 0;
}

uint32_t StageServerLobby::doWindowEvents(sf::Event & event)
{
    ContextServer& cs = GET_SERVER_CONTEXT(g);
    return 0;
}

uint32_t StageServerLobby::doLocalInputs()
{
    ContextServer& cs = GET_SERVER_CONTEXT(g);
    return 0;
}

uint32_t StageServerLobby::doDraw()
{
    ContextServer& cs = GET_SERVER_CONTEXT(g);
    return 0;
}

uint32_t StageServerLobby::cleanup()
{
    ContextServer& cs = GET_SERVER_CONTEXT(g);
    return 0;
}

}//end namespace bali



