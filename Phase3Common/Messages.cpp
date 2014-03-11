#include "Messages.h"
#include "Comm.h"
#include "Player.h"
#include <iostream>

namespace bali{


int Messages::sendReady(Comm & comm, Player & player)
{
    std::cout << "Sent Ready" << std::endl;
    CommEvent event;
    event.connectionId = player.connectionId;
    event.packet << CommEventType::Data;
    event.packet << MsgId::Ready;
    comm.Send(event);
    return 0;
}


int Messages::sendStateOfPlayer(Comm & comm, Player & player)
{
    //std::cout << "Sent StateOfPlayer" << std::endl;
    CommEvent event;
    event.connectionId = player.connectionId;
    event.packet << CommEventType::Data;
    event.packet << MsgId::StateOfPlayer;
    comm.Send(event);
    return 0;
}
int Messages::sendWhoIs(Comm & comm, Player & player)
{
    std::cout << "Sent WhoIs" << std::endl;
    CommEvent event;
    event.connectionId = player.connectionId;
    event.packet << CommEventType::Data;
    event.packet << MsgId::WhoIs;
    comm.Send(event);
    return 0;
}



int Messages::sendId(Comm & comm, Player & player)
{
    std::cout << "Sent Id" << std::endl;
    CommEvent event;
    event.connectionId = player.connectionId;
    event.packet << CommEventType::Data;
    event.packet << MsgId::Id;
//    event.packet << name;
//    event.packet << team;
    comm.Send(event);
    return 0;
}

int Messages::sendMap(Comm & comm, Player & player)
{
    std::cout << "Sent Map" << std::endl;
    CommEvent event;
    event.connectionId = player.connectionId;
    event.packet << CommEventType::Data;
    event.packet << MsgId::Map;
//    event.packet << name;
    comm.Send(event);
    return 0;
}

int Messages::sendWhoIsAck(Comm & comm, Player & player, ManagerPlayer & mp)
{
    std::cout << "Sent WhoIsAck" << std::endl;
    CommEvent event;
    event.connectionId = player.connectionId;
    event.packet << CommEventType::Data;
    event.packet << MsgId::WhoIsAck;
//    //Team 1 & 2
//    for (int t = 1;t < 3;t++){
//        event.packet << (sf::Uint32)teamMan.teams[t].players.size();//.getTeamSize(1);
//        for (auto y= teamMan.teams[t].players.begin();y != teamMan.teams[t].players.end();y++){
//            event.packet << y->playerName;
//        }
//    }

    comm.Send(event);
    return 0;
}

int Messages::sendIdAck(Comm & comm, Player & player, ManagerPlayer & mp)
{
    std::cout << "Sent IdAck" << std::endl;
    CommEvent event;
    event.connectionId = player.connectionId;
    event.packet << CommEventType::Data;
    event.packet << MsgId::IdAck;
//    event.packet << slot;
    comm.Send(event);
    return 0;
}
int Messages::sendIdNack(Comm & comm, Player & player)
{
    std::cout << "Sent IdNack" << std::endl;
    CommEvent event;
    event.connectionId = player.connectionId;
    event.packet << CommEventType::Data;
    event.packet << MsgId::IdNack;
    comm.Send(event);
    return 0;
}


int Messages::sendStateOfUnion(Comm & comm)
{
    std::cout << "Sent StateOfUnion" << std::endl;
    CommEvent event;
    event.connectionId = -1;
    event.packet << CommEventType::Data;
    event.packet << MsgId::StateOfUnion;
    comm.Send(event);
    return 0;
}

int Messages::sendStart(Comm & comm)
{
    std::cout << "Sent Start" << std::endl;
    CommEvent event;
    event.connectionId = -1;
    event.packet << CommEventType::Data;
    event.packet << MsgId::Start;
    comm.Send(event);

    return 0;
}

}//end namespace bali
