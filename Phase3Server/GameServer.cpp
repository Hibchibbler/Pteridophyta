#include "GameServer.h"
#include "StageServerStart.h"
#include "StageServerLobby.h"
#include "StageServerMain.h"

namespace bali{

GameServer::GameServer()
    : Game()
{
}

GameServer::~GameServer()
{

}

sf::Uint32 GameServer::initialize()
{
    //Allocate memory for context
    setContext(new ContextServer());

    add(std::shared_ptr<GameStage>(new StageServerStart(*this, 0)));//0 - uid for setup stage
    add(std::shared_ptr<GameStage>(new StageServerLobby(*this, 1)));//1 - uid for lobby stage
    add(std::shared_ptr<GameStage>(new StageServerMain(*this, 2)));//2 - uid for main stage

    server.StartServer(5676);
    return 0;
}
sf::Uint32 GameServer::doEventProcessing()
{
    //Do remote processing
    CommEvent event;
    while (server.Receive(event)){
        sf::Uint32 t;
        event.packet >> t;
        switch (t){
            case CommEventType::Connected:{
                //Server accepted a remote hosts connection request
                //Through Connected, and Disconnect, we are able to keep track of particular connections.
                //the connection id we get from connected (in the packet payload), is that which we use to,later, send things to the
                //server from this particular connection.
                std::cout << "Connected." <<  std::endl;

                //
                //The Connect Comm Event Type packs the connections'
                //connectionId as part of payload.
                //Disconnect also works this way.
                //
                sf::Uint32 cid;
                event.packet >> cid;

                SPlayer np(new Player);
                np->connectionId = cid;
                mp.players.push_back(np);

                break;
            }case CommEventType::Disconnect:{
                //Server is no longer connected to a remote host
                std::cout << "Disconnected." << std::endl;

                sf::Uint32 cid;
                event.packet >> cid;
                mp.removePlayerByCid(cid);

                break;
            }case CommEventType::Error:
                //An error has occured in the Server
                std::cout << "Error." << std::endl;
                break;
            case CommEventType::Data:{
                //Delegate this event to the current stage
                std::cout << "Data." <<std::endl;
                getCurrentStage()->doRemoteEvents(event);
                break;
            }
        }
    }
    return 0;
}
sf::Uint32 GameServer::doGameProcessing()
{
    //doLoop
    Game::doGameProcessing();
    return 0;
}
sf::Uint32 GameServer::cleanup()
{
    Game::cleanup();
    return 0;
}
}//end namespace bali

