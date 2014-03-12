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
//
    SPlayer s = gs->mp.getSpectatorByCid(cid);
    SPlayer p = gs->mp.getPlayerByCid(cid);
    if (s == nullptr && p == nullptr){
        //a player with cid does not exist
        return STAGE_SERVER_LOBBY_ERROR;
    }
    switch (msgId){
        case MsgId::WhoIs:{
            std::cout << "Got WhoIs" << std::endl;

            Messages::sendWhoIsAck(gs->server, *s.get(), gs->mp);
            //p->stateServer = StatePlayerServer::SendWhoIsAck;
            break;
        }case MsgId::Id:{
            std::cout << "Got Id" << std::endl;
            //If Id is valid then
            // SendIdAck
            //Else
            // SendIdNack
            gs->mp.players.push_back(s);
            gs->mp.removeSpectatorByCid(cid);
            //TODO: Combine these Map into IdAck
            Messages::sendIdAck(gs->server,*s.get(),gs->mp);
            //Messages::sendMap(gs->server, *(*p));
            //p->stateServer = StatePlayerServer::SendIdAck;

            break;
        }case MsgId::Ready:{
            std::cout << "Got Ready" << std::endl;
            //Tally these up.
            //When tally equals num players, Start.
             Messages::sendStart(gs->server);
            break;
        }
    }
    return STAGE_SERVER_LOBBY_SUCCESS;
}

sf::Uint32 StageServerLobby::doLoop()
{
    GameServer* gs = ((GameServer*)&g);

//    for (auto pi = gs->mp.players.begin();
//         pi != gs->mp.players.end();
//         pi++){
//
//        sf::Uint32 s = (*pi)->stateServer;
//        switch (s){
//        case StatePlayerServer::Waiting:
//            break;
//        case StatePlayerServer::SendWhoIsAck:
//            std::cout << "Sent WhoIsAck." << std::endl;
//            Messages::sendWhoIsAck(gs->server, *(*pi), gs->mp);
//            s = StatePlayerServer::Waiting;
//            break;
//        case StatePlayerServer::SendIdAck:
//            std::cout << "Sent IdAck." << std::endl;
//            //Players' name and team is established.
//            s = StatePlayerServer::SendMap;
//            break;
//        case StatePlayerServer::SendMap:
//            std::cout << "Sent Map." << std::endl;
//            Messages::sendMap(gs->server, *(*pi));
//            s = StatePlayerServer::Waiting;//WaitReady
//            break;
//        case StatePlayerServer::SendIdNack:
//            std::cout << "Sent IdNack." << std::endl;
//            s = StatePlayerServer::Waiting;
//            break;
//        }
//        (*pi)->stateServer = s;
//    }

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



