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

    ctx.mc.initialize("configuration.xml");
    ctx.mm.initialize(ctx.mc);
    ctx.mt.initialize(ctx.mm);
    ctx.mw.initialize(ctx.mc, ctx.mm);

    ctx.screenWidth = ctx.mc.client.window.width;
    ctx.screenHeight = ctx.mc.client.window.height;

    ctx.window.create(sf::VideoMode(ctx.mc.client.window.width,
                                    ctx.mc.client.window.height,
                                    32), "Bam");

    return 0;
}
uint32_t GameClient::doEventProcessing()
{
    //Initialize the current stage
    Game::doEventProcessing();

    //Do remote processing
    CommEvent event;
    while (ctx.net.receive(event)){
        uint32_t t;
        (*event.packet) >> t;
        switch (t){
            case CommEventType::Connected:{
                //Local Host has connected to Server
                std::cout << "Connected." << std::endl;
                ctx.mp.player.connectionId = event.connectionId;
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
    while (ctx.window.pollEvent(wevent))
    {
        getCurrentStage()->doWindowEvent(wevent);
        if (wevent.type == sf::Event::Resized)
        {
            ctx.screenWidth = wevent.size.width;
            ctx.screenHeight = wevent.size.height;
            std::cout << "GameClient::Resize  " << ctx.screenWidth << ", " << ctx.screenHeight << std::endl;
        }else if (wevent.type == sf::Event::Closed)
        {
            ctx.window.close();
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
