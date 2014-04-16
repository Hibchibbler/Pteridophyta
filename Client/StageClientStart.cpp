#include "StageClientStart.h"
#include "GameClient.h"

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
    compStartWindow.initialize(cc);

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
    compStartWindow.doWindowEvent(cc, event);

    return 0;
}
uint32_t StageClientStart::doLocalInputs()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    compStartWindow.doLocalInputs(cc);

    return 0;
}

uint32_t StageClientStart::doUpdate()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    compStartWindow.doUpdate(cc);
    if (compStartWindow.isStarted())
    {
        finished(0);
    }

    return 0;
}
uint32_t StageClientStart::doDraw()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    cc.window.clear();
    cc.window.resetGLStates();

    compStartWindow.doDraw(cc);

    //cc.sfGui.Display(cc.window);
    cc.window.display();
    return 0;
}
uint32_t StageClientStart::cleanup()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    compStartWindow.cleanup(cc);
    return 0;
}


}//end namespace bali
