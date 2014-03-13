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
            stateClient = StatePlayerClient::Waiting;
            stateServer = StatePlayerServer::Waiting;
            identified = 0;
            ready = 0;
        }

        //Mark the player as identified.
        void setIdentity()
        {
            identified = 1;
        }

        bool isIdentified()
        {
            return (identified==1);
        }

        void setReady()
        {
            ready = 1;
        }

        bool isReady()
        {
            return (ready==1);
        }

        std::string name;
        sf::Uint32 team;
        sf::Uint32 connectionId;

        //
        //These are for the lobby
        //
        sf::Uint32 identified;
        sf::Uint32 ready;

        union{
            //
            //State used by client
            //
            sf::Uint32 stateClient;

            //
            //State used by server
            //
            sf::Uint32 stateServer;
        };

    };

    typedef std::shared_ptr<Player> SPlayer;

}//end namespace bali

#endif
