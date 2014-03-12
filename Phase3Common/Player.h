#ifndef Player_h_
#define Player_h_

#include <memory>
#include <SFML/Graphics.hpp>
//#include "Projectile.h"
//#include "Tank.h"

namespace bali
{
    struct StatePlayerClient{
        enum cstate{
            Waiting,
            SendWhoIs,
            WaitWhoIsAck,
            SendId,
            WaitIdAck,
            WaitMap,
            SendReady,
            WaitStart,
            Established
        };
    };

    struct StatePlayerServer{
        enum sstate{
            Waiting,
            SendWhoIsAck,
            SendIdAck,
            SendIdNack,
            SendMap,
            SendStart,
            WaitWhoIs,
            WaitId,
            WaitReady,
            Established
        };
    };


    class Player
    {
    public:
        Player(){
            name = "?";
            connectionId = -1;
            stateClient = StatePlayerClient::SendWhoIs;
            stateServer = StatePlayerServer::Waiting;
        }

        std::string name;
        sf::Uint32 team;
        sf::Uint32 connectionId;
        sf::Uint32 stateClient;
        sf::Uint32 stateServer;

    };

    typedef std::shared_ptr<Player> SPlayer;

}//end namespace bali

#endif
