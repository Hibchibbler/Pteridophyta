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

uint32_t StageClientStart::initialize()
{
    Context& ctx = g->ctx;
    //Add Components
    components.push_back(std::make_shared<CompWindowStart>(this));

    //Initialize components
    for (auto& c : components)
    {
        c->initialize(ctx);
    }

    //Set this so Game knows we are initialized, so it won't
    // initialize us again.
    initialized();
    return 0;
}

uint32_t StageClientStart::doRemoteEvent(CommEvent & event)
{
    return 0;
}

uint32_t StageClientStart::doWindowEvent(sf::Event & event)
{
    Context& ctx = g->ctx;
    for (auto& c : components)
    {
        c->doWindowEvent(ctx, event);
    }

    return 0;
}
uint32_t StageClientStart::doLocalInputs()
{
    Context& ctx = g->ctx;
    for (auto& c : components)
    {
        c->doLocalInputs(ctx);
    }

    return 0;
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
}

uint32_t StageClientStart::doUpdate()
{
    Context& ctx = g->ctx;
    //Process Stage Commands
    processCommands(nullptr);

    for (auto& c : components)
    {
        c->doUpdate(ctx);
    }

    return 0;
}
uint32_t StageClientStart::doDraw()
{
    Context& ctx = g->ctx;
    ctx.window.clear();
    ctx.window.resetGLStates();

    for (auto& c : components)
    {
        c->doDraw(ctx);
    }

    ctx.window.display();
    return 0;
}
uint32_t StageClientStart::cleanup()
{
    Context& ctx = g->ctx;
    for (auto& c : components)
    {
        c->cleanup(ctx);
    }
    return 0;
}


}//end namespace bali
