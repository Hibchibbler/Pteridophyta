#ifndef GameClient_h_
#define GameClient_h_

#include "Game.h"
#include "Context.h"

namespace bali
{
    #define GET_CLIENT_CONTEXT(g) (((GameClient*)g)->ctx)

    //this is the client-side game object.
    class GameClient : public Game
    {
    public:
        GameClient();
        ~GameClient();
        uint32_t initialize();
        uint32_t doEventProcessing();
        uint32_t doGameProcessing();
        uint32_t cleanup();

        uint32_t processCommands(void* arg){return 0;}

    private:
    };
}
#endif // GameClient_h_
