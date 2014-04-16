#include "Messages.h"
#include "Comm.h"
#include "Player.h"
#include "ManagerPlayer.h"
#include "ManagerConfiguration.h"
#include <iostream>

namespace bali{




int Messages::sendReady(Comm & comm, Player & player)
{
    std::cout << "Sent Ready" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, player.connectionId);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::Ready;
    comm.send(event);
    return 0;
}


int Messages::sendStateOfPlayer(Comm & comm, Player & player)
{
    //std::cout << "Sent StateOfPlayer" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, player.connectionId);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::StateOfPlayer;
    comm.send(event);
    return 0;
}
int Messages::sendWhoIs(Comm & comm, Player & player)
{
    std::cout << "Sent WhoIs" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, player.connectionId);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::WhoIs;
    comm.send(event);
    return 0;
}



int Messages::sendId(Comm & comm, Player & player)
{
    std::cout << "Sent Id" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, player.connectionId);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::Id;
    (*event.packet) << player.name;
    (*event.packet) << player.team;
    comm.send(event);
    return 0;
}

//int Messages::sendMap(Comm & comm, Player & player)
//{
//    std::cout << "Sent Map" << std::endl;
//    CommEvent event;
//    event.connectionId = player.connectionId;
//    (*event.packet) << CommEventType::Data;
//    (*event.packet) << MsgId::Map;
////    (*event.packet) << name;
//    comm.Send(event);
//    return 0;
//}

int Messages::sendWhoIsAck(Comm & comm, SPlayer player, ManagerPlayer & mp)
{
    std::cout << "Sent WhoIsAck" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, player->connectionId);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::WhoIsAck;

    uint32_t numPlayers=0;
    for (int i = 0;i < mp.players.size();i++){
        if (mp.players[i]->isIdentified())
            numPlayers++;
    }
    std::cout << "sendWhoIsAck (" << numPlayers << ")"<<std::endl;
    (*event.packet) << numPlayers;
    for (const auto &p : mp.players)
    {

        if (p->isIdentified()){
            std::cout << "\t" << p->name << std::endl;
            (*event.packet) << p->name << p->team;
        }
    }
    std::cout << std::endl;

    comm.send(event);
    return 0;
}

int Messages::sendIdAck(Comm & comm, SPlayer player, ManagerPlayer & mp, ManagerConfiguration& mc)
{
    std::cout << "Sent IdAck" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, player->connectionId);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::IdAck;

    //server will send layer name as found in configuration.xml
    //this layer name indicates which layer, in the tmx file to use for the level.
    //TODO rethink this.
    (*event.packet) << mc.configuration.global.maps.front().id;

    comm.send(event);
    return 0;
}
int Messages::sendIdNack(Comm & comm, SPlayer player)
{
    std::cout << "Sent IdNack" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, player->connectionId);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::IdNack;
    comm.send(event);
    return 0;
}


int Messages::sendStateOfUnion(Comm & comm)
{
    std::cout << "Sent StateOfUnion" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, -1);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::StateOfUnion;
    comm.send(event);
    return 0;
}

int Messages::sendStart(Comm & comm)
{
    std::cout << "Sent Start" << std::endl;
    CommEvent event;
    Comm::initializeCommEvent(event, -1);

    (*event.packet) << CommEventType::Data;
    (*event.packet) << MsgId::Start;
    comm.send(event);

    return 0;
}

}//end namespace bali
