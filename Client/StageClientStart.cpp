#include "StageClientStart.h"
#include "GameClient.h"

#include "CompWindowStart.h"
#include <iostream>

namespace bali{

StageClientStart::StageClientStart(Game* game, uint32_t uid)
 :  Stage(game, uid)
{
}

StageClientStart::~StageClientStart()
{
}

ReturnVal StageClientStart::initialize()
{
    //Add Components
    components.push_back(std::make_shared<CompWindowStart>(this));

    //Initialize components
    for (auto& c : components)
    {
        c->initialize();
    }

    //Set this so Game knows we are initialized, so it won't
    // initialize us again.
    initialized();
    return ReturnVal();
}

ReturnVal StageClientStart::doRemoteEvent(CommEvent & event)
{
    return ReturnVal();
}

ReturnVal StageClientStart::doWindowEvent(sf::Event & event)
{
    for (auto& c : components)
    {
        c->doWindowEvent(event);
    }

    return ReturnVal();
}
ReturnVal StageClientStart::doLocalInputs()
{
    for (auto& c : components)
    {
        c->doLocalInputs();
    }

    return ReturnVal();
}
uint32_t StageClientStart::processCommands(void* arg)
{
    for (auto& i : commands)
    {
        switch (i->getFunction())
        {
            case CommandStage::Functions::STAGEFINISH:
                std::cout << "Processing STAGEFINISH" << std::endl;
                finished(0);
                break;
        }
    }

    commands.clear();
    return 0;
}

ReturnVal StageClientStart::doUpdate()
{
    //Process Stage Commands
    processCommands(nullptr);

    for (auto& c : components)
    {
        c->doUpdate();
    }

    return ReturnVal();
}
ReturnVal StageClientStart::doDraw()
{
    Context& ctx = game->ctx;
    ctx.window.clear();
    ctx.window.resetGLStates();

    for (auto& c : components)
    {
        c->doDraw();
    }

    ctx.window.display();
    return ReturnVal();
}
ReturnVal StageClientStart::cleanup()
{
    for (auto& c : components)
    {
        c->cleanup();
    }
    return ReturnVal();
}


}//end namespace bali
