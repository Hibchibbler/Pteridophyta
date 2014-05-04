#ifndef Messages_h_
#define Messages_h_

#include <memory>
#include "CommandStage.h"
#include "CommandComponent.h"
//#include <vector>
//#include <string>
//#include <SFML/Config.hpp>

namespace bali
{
    struct MsgId {enum mid{
        WhoIs,
        WhoIsAck,
        Id,
        IdAck,
        IdNack,
        Ready,
        Start,
        StateOfUnion,
        StateOfPlayer,
        Map
    };};

    class Comm;
    class Player;
    typedef std::shared_ptr<Player> SPlayer;
    class ManagerPlayer;
    class ManagerConfiguration;
    class Messages
    {
    public:

    //Client messages
        static int sendReady            (Comm & comm, Player & player);
        static int sendStateOfPlayer    (Comm & comm, Player & player);
        static int sendWhoIs            (Comm & comm, Player & player);
        static int sendId               (Comm & comm, Player & player);
    //Server messages
        static int sendWhoIsAck         (Comm & comm, SPlayer player, ManagerPlayer & mp);
        static int sendIdAck            (Comm & comm, SPlayer player, ManagerPlayer & mp, ManagerConfiguration& mc);
        static int sendIdNack           (Comm & comm, SPlayer player);
        static int sendStateOfUnion     (Comm & comm);
        static int sendStart            (Comm & comm);



    private:

    };



};


#endif
