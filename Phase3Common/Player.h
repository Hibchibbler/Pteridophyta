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
        uint32_t team;
        uint32_t connectionId;

        //
        //These are for the lobby
        //
        uint32_t identified;
        uint32_t ready;

        union{
            //
            //State used by client
            //
            uint32_t stateClient;

            //
            //State used by server
            //
            uint32_t stateServer;
        };

    };

    typedef std::shared_ptr<Player> SPlayer;

}//end namespace bali

#endif
