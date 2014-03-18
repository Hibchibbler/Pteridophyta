#include "StageServerMain.h"

namespace bali{

StageServerMain::StageServerMain(Game & game, uint32_t uid)
    :  GameStage(game, uid)
{

}
StageServerMain::~StageServerMain()
{

}
uint32_t StageServerMain::initialize()
{
    initialized();
    return 0;
}
uint32_t StageServerMain::doRemoteEvents(CommEvent & cevent)
{
    return 0;
}
uint32_t StageServerMain::doWindowEvents(sf::Event & wevent)
{
    return 0;
}
uint32_t StageServerMain::doLocalInputs()
{
    return 0;
}
uint32_t StageServerMain::doLoop()
{
    //finished(0);
    return 0;
}
uint32_t StageServerMain::doDraw()
{
    return 0;
}
uint32_t StageServerMain::cleanup()
{
    return 0;
}

}//end namespace bali
