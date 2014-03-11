#include "StageServerLobby.h"
#include "Comm.h"
#include "ManagerPlayer.h"
//#include "ManagerArena.h"
#include "GameServer.h"
#include "Messages.h"
#include <iostream>


namespace bali{

StageServerLobby::StageServerLobby(Game & g, sf::Uint32 uid)
    : GameStage(g, uid)
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
        //a player with cid does not exist
        return STAGE_SERVER_LOBBY_ERROR;
    }
    switch (msgId){
        case MsgId::WhoIs:{
            std::cout << "Got WhoIs" << std::endl;
            Messages::sendWhoIsAck(cevent, p);
            break;
        }case MsgId::Id:{
            break;
        }case MsgId::Ready:{
            std::cout << "Got Ready" << std::endl;
            break;
        }case MsgId::StateOfPlayer:{
            std::cout << "Got StateOfPlayer" << std::endl;
            break;
        }
    }
    return STAGE_SERVER_LOBBY_SUCCESS;
}

sf::Uint32 StageServerLobby::doLoop()
{
    GameServer* gs = ((GameServer*)&g);

    for (auto pi = gs->mp.players.begin();
         pi != gs->mp.players.end();
         pi++){

        sf::Uint32 s = (*pi)->serverState;
        switch (s){
        case StatePlayerServer::New:
            break;
        case StatePlayerServer::SendWhoIsAck:
            Messages::sendWhoIsAck(gc->client, *(*pi));
            s = StatePlayerServer::New;
            break;
        case StatePlayerServer::SendIdAck:
            s = StatePlayerServer::SendMap;
            break;
        case StatePlayerServer::SendIdNack:
            s = StatePlayerServer::New;
            break;
        case StatePlayerServer::SendMap:
            s = StatePlayerServer::WaitReady
            break;
        }
        (*pi)->serverState = s;
    }

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



