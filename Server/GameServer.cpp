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

uint32_t GameServer::initialize()
{
    add(std::shared_ptr<Stage>(new StageServerStart(this, 0)));//0 - uid for setup stage
    add(std::shared_ptr<Stage>(new StageServerLobby(this, 1)));//1 - uid for lobby stage
    add(std::shared_ptr<Stage>(new StageServerMain(this, 2)));//2 - uid for main stage

    cs.mc.initialize("configuration.xml");
    cs.mm.initialize(cs.mc);
    cs.mw.initialize(cs.mc, cs.mm);

    uint32_t port = atoi(cs.mc.configuration.server.properties["port"].c_str());
    std::cout << "Listening on Port " << port << std::endl;
    cs.net.startServer(5676);
    return 0;
}
uint32_t GameServer::doEventProcessing()
{
    //Initialize the current stage
    Game::doEventProcessing();

    //Do remote processing
    CommEvent event;
    while (cs.net.receive(event)){
        uint32_t t;
        (*event.packet) >> t;
        switch (t){
            case CommEventType::Connected:{
                //Server accepted a remote hosts connection request
                std::cout << "Connected." <<  std::endl;

                SPlayer newPlayer(new Player);
                newPlayer->connectionId = event.connectionId;//cid;
                cs.mp.addPlayer(newPlayer);

                break;
            }case CommEventType::Disconnect:{
                //Server is no longer connected to a remote host
                std::cout << "Disconnected." << std::endl;
                cs.mp.removePlayerByCid(event.connectionId);
                break;
            }case CommEventType::Error:
                //An error has occured in the Server
                std::cout << "Error." << std::endl;
                break;
            case CommEventType::Data:{
                //Delegate this event to the current stage
                std::cout << "Data." <<std::endl;
                getCurrentStage()->doRemoteEvent(event);
                break;
            }
        }
    }
    return 0;
}
uint32_t GameServer::doGameProcessing()
{
    //doUpdate
    Game::doGameProcessing();
    return 0;
}
uint32_t GameServer::cleanup()
{
    Game::cleanup();
    return 0;
}
}//end namespace bali

