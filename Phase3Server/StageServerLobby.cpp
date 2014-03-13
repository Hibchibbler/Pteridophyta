#include "StageServerLobby.h"
#include "Comm.h"
#include "ManagerPlayer.h"
//#include "ManagerArena.h"
#include "GameServer.h"
#include "Messages.h"
#include <iostream>


namespace bali{

StageServerLobby::StageServerLobby(Game & game, sf::Uint32 uid)
    : GameStage(game, uid)
{
}

StageServerLobby::~StageServerLobby()
{
}

sf::Uint32 StageServerLobby::initialize()
{
    initialized();
    return 0;
}

sf::Uint32 StageServerLobby::doRemoteEvents(CommEvent & cevent)
{
    GameServer* gs = ((GameServer*)&g);

    sf::Uint32 msgId;
    sf::Uint32 cid;

    cid = cevent.connectionId;
    cevent.packet >> msgId;

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
            p->setIdentity();

            Messages::sendIdAck(gs->server, p,gs->mp);
            //Messages::sendIdNack(gs->server, p);
            break;
        }case MsgId::Ready:{
            std::cout << "Got Ready" << std::endl;
            p->setReady();
            Messages::sendStart(gs->server);
            break;
        }
    }
    return STAGE_SERVER_LOBBY_SUCCESS;
}

sf::Uint32 StageServerLobby::doLoop()
{
    GameServer* gs = ((GameServer*)&g);

    return 0;
}

sf::Uint32 StageServerLobby::doWindowEvents(sf::Event & wevent)
{

    return 0;
}

sf::Uint32 StageServerLobby::doLocalInputs()
{

    return 0;
}

sf::Uint32 StageServerLobby::doDraw()
{
    return 0;
}

sf::Uint32 StageServerLobby::cleanup()
{
    return 0;
}

}//end namespace bali



