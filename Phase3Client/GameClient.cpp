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
    //client.StartClient(9786, "127.0.0.1");
    setContext(new ContextClient());

    add(std::shared_ptr<GameStage>(new StageClientStart(*this, 0)));//0 - uid for setupstage
    add(std::shared_ptr<GameStage>(new StageClientLobby(*this, 1)));//0 - uid for setupstage
    add(std::shared_ptr<GameStage>(new StageClientMain(*this, 2)));//1 - uid for mainstage


    mc.initialize("configuration.xml");
    mm.initialize(mc);
    mt.initialize(mm);
    mw.initialize(mc, mm);

    window.create(sf::VideoMode(900,800,32), "Bam");

    return 0;
}
sf::Uint32 GameClient::doEventProcessing()
{

    //Do remote processing
    CommEvent event;
    while (client.Receive(event)){
        sf::Uint32 t;
        event.packet >> t;
        switch (t){
            case CommEventType::Connected:{
                //Local Host has connected to Server
                std::cout << "Connected." << std::endl;/// << msgId << std::endl;

                mp.player.connectionId = event.connectionId;
                break;
            }case CommEventType::Disconnect:{
                //Local Host is disconnected from Server
                std::cout << "Disconnected." <<std::endl;
                break;
            }case CommEventType::Error:
                //An error has occured in the Server
                std::cout << "Error." << std::endl;// << msgId << std::endl;
                break;
            case CommEventType::Data:{
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
