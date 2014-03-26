#include "GameClient.h"
#include "StageClientStart.h"
#include "StageClientLobby.h"
#include "StageClientMain.h"

namespace bali{
#define CLIENTCONTEXT ((ContextClient*)getContext())

GameClient::GameClient()
    : Game()
{

}

GameClient::~GameClient()
{
}

uint32_t GameClient::initialize()
{
    setContext(new ContextClient());

    add(std::make_shared<StageClientStart>(*this, 0));//0 - uid for start stage
    add(std::make_shared<StageClientLobby>(*this, 1));//1 - uid for lobby stage
    add(std::make_shared<StageClientMain>(*this, 2));//2 - uid for main stage

    mc.initialize("configuration.xml");
    mm.initialize(mc);
    //mt.initialize(mm);
    mw.initialize(mc, mm);

    CLIENTCONTEXT->screenWidth = mc.configuration.client.window.width;
    CLIENTCONTEXT->screenHeight = mc.configuration.client.window.height;

    window.create(sf::VideoMode(mc.configuration.client.window.width,
                                mc.configuration.client.window.height,
                                32), "Bam");

    return 0;
}
uint32_t GameClient::doEventProcessing()
{
    //Do remote processing
    CommEvent event;
    while (client.receive(event)){
        uint32_t t;
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
                getCurrentStage()->doRemoteEvent(event);
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
            CLIENTCONTEXT->screenWidth = wevent.size.width;
            CLIENTCONTEXT->screenHeight = wevent.size.height;
            std::cout << "GameClient::Resize  " << CLIENTCONTEXT->screenWidth << ", " << CLIENTCONTEXT->screenHeight << std::endl;
        }else if (wevent.type == sf::Event::Closed)
        {
            window.close();
            return 1;
        }
    }

    getCurrentStage()->doLocalInputs();
    return 0;
}
uint32_t GameClient::doGameProcessing()
{
    //doUpdate
    //doDraw
    Game::doGameProcessing();
    return 0;
}
uint32_t GameClient::cleanup()
{
    Game::cleanup();
    return 0;
}


}
