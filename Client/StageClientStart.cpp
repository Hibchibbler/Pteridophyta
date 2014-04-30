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
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    //Add Components
    components.push_back(std::make_shared<CompWindowStart>(this));

    //Initialize components
    for (auto& c : components)
    {
        c->initialize(cc);
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
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    for (auto& c : components)
    {
        c->doWindowEvent(cc, event);
    }

    return 0;
}
uint32_t StageClientStart::doLocalInputs()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    for (auto& c : components)
    {
        c->doLocalInputs(cc);
    }

    return 0;
}
uint32_t StageClientStart::processCommands(void* arg)
{
    for (auto& i : commands)
    {
        switch (i.getFunction())
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
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    //Process Stage Commands
    processCommands(nullptr);

    for (auto& c : components)
    {
        c->doUpdate(cc);
    }

    return 0;
}
uint32_t StageClientStart::doDraw()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    cc.window.clear();
    cc.window.resetGLStates();

    for (auto& c : components)
    {
        c->doDraw(cc);
    }

    cc.window.display();
    return 0;
}
uint32_t StageClientStart::cleanup()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    for (auto& c : components)
    {
        c->cleanup(cc);
    }
    return 0;
}


}//end namespace bali
