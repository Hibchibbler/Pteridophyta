#include "GameClient.h"
#include "StageClientStart.h"
#include "StageClientLobby.h"
#include "StageClientMain.h"

namespace bali{

GameClient::GameClient()
    : Game()
{

}

GameClient::~GameClient()
{
}

sf::Uint32 GameClient::initialize()
{
    setContext(new ContextClient());

    add(std::shared_ptr<GameStage>(new StageClientStart(*this, 0)));//0 - uid for start stage
    add(std::shared_ptr<GameStage>(new StageClientLobby(*this, 1)));//1 - uid for lobby stage
    add(std::shared_ptr<GameStage>(new StageClientMain(*this, 2)));//2 - uid for main stage

    mc.initialize("configuration.xml");
    mm.initialize(mc);
    mt.initialize(mm);
    mw.initialize(mc, mm);

    window.create(sf::VideoMode(600,500,32), "Bam");

    return 0;
}
sf::Uint32 GameClient::doEventProcessing()
{
    //Do remote processing
    CommEvent event;
    while (client.receive(event)){
        sf::Uint32 t;
        (*event.packet) >> t;
        switch (t){
            case CommEventType::Connected:{
                //Local Host has connected to Server
                std::cout << "Connected." << std::endl;
                mp.player.connectionId = event.connectionId;
                break;
            }case CommEventType::Disconnect:{
                //Local Host is disconnected from Server
                std::cout << "Disconnected." <<std::endl;

                break;
            }case CommEventType::Error:
                //An error has occured in the Server
                std::cout << "Error." << std::endl;
                break;
            case CommEventType::Data:{
                std::cout << "Data." << std::endl;
                //Delegate this event to the current stage
                getCurrentStage()->doRemoteEvents(event);
                break;
            }
        }
    }

    sf::Event wevent;
    while (window.pollEvent(wevent))
    {
        getCurrentStage()->doWindowEvents(wevent);
        if (wevent.type == sf::Event::Resized)
        {
            winWidth = wevent.size.width;
            winHeight = wevent.size.height;
            std::cout << winWidth << ", " << winHeight << std::endl;
        }else if (wevent.type == sf::Event::Closed)
        {
            window.close();
            return 1;
        }
    }

    getCurrentStage()->doLocalInputs();
    return 0;
}
sf::Uint32 GameClient::doGameProcessing()
{
    //doLoop
    //doDraw
    Game::doGameProcessing();
    return 0;
}
sf::Uint32 GameClient::cleanup()
{
    Game::cleanup();
    return 0;
}


}
