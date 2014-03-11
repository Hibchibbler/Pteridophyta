#ifndef Player_h_
#define Player_h_

#include <memory>
#include <SFML/Graphics.hpp>
//#include "Projectile.h"
//#include "Tank.h"

namespace bali
{
    //This enum is used by both server and client entities
    //to identify state. so, some states don't make sense from a client
    //perspective, and likewise for server.
    struct PlayerState{
        enum pstate{
            New,/***********/
            SendingWhoIs,//p
            SendingWhoIsAck,//s
            WaitingForWhoIsAck,//p
            SendingId,//p
            SendingIdAck,//s
            SendingIdNack,//s
            WaitingForIdAck,//p
            SendingStateOfPlayer,//p
            WaitingForStateOfPlayer,//s?
            SendingStateOfUnion,//s
            WaitingForStateOfUnion,//p
            SendingReady,//p
            WaitingForReady,//s
            Ready,/***********/
            WaitingForMap,//p
            WaitingForStart,//
            Running,/***********/
            Paused,/***********/
            EmitProjectile
        };
    };

    struct StatePlayerClient{
        enum cstate{
            New,
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
            New,
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
            name = "-empty-";
            connectionId = -1;
            state = PlayerState::New;
            isLocalPlayer = false;
            slotNum = -1;
            stateClient = StatePlayerClient::New;
            stateServer = StatePlayerServer::New;
        }

        std::string name;
        sf::Uint32 team;
        sf::Uint32 connectionId;
        sf::Uint32 isLocalPlayer;
        sf::Uint32 slotNum;
        sf::Uint32 state;
        sf::Uint32 stateClient;
        sf::Uint32 stateServer;

    };

    typedef std::shared_ptr<Player> SPlayer;

}//end namespace bali

#endif
