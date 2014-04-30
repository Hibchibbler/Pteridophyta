#ifndef Player_h_
#define Player_h_

#include <memory>
#include <queue>
#include <SFML/Graphics.hpp>
#include "Commandable.h"
#include "CommandPlayer.h"


namespace bali
{
    struct StatePlayerClient{
        enum cstate{
            Waiting,
            SendWhoIs,
            SendId,
            SendReady,
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
            Established
        };
    };


    class Player : public Commandable<CommandPlayer>
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
        std::string pass;
        uint32_t server_port;
        std::string server_ip;

        uint32_t team;



        uint32_t connectionId;

        uint32_t identified;
        uint32_t ready;

        union{
            uint32_t stateClient;
            uint32_t stateServer;
        };

        //Boom Chick, the fun stuff
        uint32_t x;
        uint32_t y;

        uint32_t mass;

        uint32_t processCommands(void* arg)
        {
            return 0;
        }

    };

    typedef std::shared_ptr<Player> SPlayer;

}//end namespace bali

#endif
