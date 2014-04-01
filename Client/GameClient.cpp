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

uint32_t GameClient::initialize()
{
    add(std::make_shared<StageClientStart>(this, 0));//0 - uid for start stage
    add(std::make_shared<StageClientLobby>(this, 1));//1 - uid for lobby stage
    add(std::make_shared<StageClientMain>(this, 2));//2 - uid for main stage

    cc.mc.initialize("configuration.xml");
    cc.mm.initialize(cc.mc);
    cc.mt.initialize(cc.mm);
    cc.mw.initialize(cc.mc, cc.mm);

    cc.screenWidth = cc.mc.configuration.client.window.width;
    cc.screenHeight = cc.mc.configuration.client.window.height;

    cc.window.create(sf::VideoMode(cc.mc.configuration.client.window.width,
                                   cc.mc.configuration.client.window.height,
                                   32), "Bam");

    return 0;
}
uint32_t GameClient::doEventProcessing()
{
    //Do remote processing
    CommEvent event;
    while (cc.net.receive(event)){
        uint32_t t;
        (*event.packet) >> t;
        switch (t){
            case CommEventType::Connected:{
                //Local Host has connected to Server
                std::cout << "Connected." << std::endl;
                cc.mp.player.connectionId = event.connectionId;
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
    while (cc.window.pollEvent(wevent))
    {
        getCurrentStage()->doWindowEvents(wevent);
        if (wevent.type == sf::Event::Resized)
        {
            cc.screenWidth = wevent.size.width;
            cc.screenHeight = wevent.size.height;
            std::cout << "GameClient::Resize  " << cc.screenWidth << ", " << cc.screenHeight << std::endl;
        }else if (wevent.type == sf::Event::Closed)
        {
            cc.window.close();
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
