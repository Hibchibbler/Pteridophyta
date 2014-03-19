#include "StageServerLobby.h"
#include "Comm.h"
#include "ManagerPlayer.h"
//#include "ManagerArena.h"
#include "GameServer.h"
#include "Messages.h"
#include <iostream>


namespace bali{

StageServerLobby::StageServerLobby(Game & game, uint32_t uid)
    : GameStage(game, uid)
{
}

StageServerLobby::~StageServerLobby()
{
}

uint32_t StageServerLobby::initialize()
{
    initialized();
    return 0;
}

uint32_t StageServerLobby::doRemoteEvent(CommEvent & event)
{
    GameServer* gs = ((GameServer*)&g);

    uint32_t msgId;
    uint32_t cid;

    cid = event.connectionId;
    (*event.packet) >> msgId;

    SPlayer p = gs->mp.getPlayerByCid(cid);
    if (p == nullptr){
        std::cout << "p == nullptr" << std::endl;
        //a player with cid does not exist
        return STAGE_SERVER_LOBBY_ERROR;
    }
    switch (msgId){
        case MsgId::WhoIs:{
            std::cout << "Got WhoIs" << std::endl;
            Messages::sendWhoIsAck(gs->server, p, gs->mp);
            break;
        }case MsgId::Id:{
            std::cout << "Got Id" << std::endl;
            (*event.packet) >> p->name;
            (*event.packet) >> p->team;

            p->setIdentity();

            Messages::sendIdAck(gs->server, p, gs->mp);
            //Messages::sendIdNack(gs->server, p);
            break;
        }case MsgId::Ready:{
            std::cout << "Got Ready" << std::endl;
            p->setReady();

            const uint32_t MINPLAYERS = 4;
            if (gs->mp.getNumPlayers() >= MINPLAYERS && gs->mp.isAllPlayersReady())
            {
                Messages::sendStart(gs->server);
            }
            break;
        }
    }
    return STAGE_SERVER_LOBBY_SUCCESS;
}

uint32_t StageServerLobby::doLoop()
{
    GameServer* gs = ((GameServer*)&g);

    return 0;
}

uint32_t StageServerLobby::doWindowEvents(sf::Event & wevent)
{

    return 0;
}

uint32_t StageServerLobby::doLocalInputs()
{

    return 0;
}

uint32_t StageServerLobby::doDraw()
{
    return 0;
}

uint32_t StageServerLobby::cleanup()
{
    return 0;
}

}//end namespace bali



