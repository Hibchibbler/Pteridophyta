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

    server.startServer(5676);
    return 0;
}
sf::Uint32 GameServer::doEventProcessing()
{
    //Do remote processing
    CommEvent event;
    while (server.receive(event)){
        sf::Uint32 t;
        (*event.packet) >> t;
        switch (t){
            case CommEventType::Connected:{
                //Server accepted a remote hosts connection request
                std::cout << "Connected." <<  std::endl;

                SPlayer newPlayer(new Player);
                newPlayer->connectionId = event.connectionId;//cid;
                mp.addPlayer(newPlayer);

                break;
            }case CommEventType::Disconnect:{
                //Server is no longer connected to a remote host
                std::cout << "Disconnected." << std::endl;
                mp.removePlayerByCid(event.connectionId);
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

