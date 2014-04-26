#include "StageServerStart.h"

namespace bali{

StageServerStart::StageServerStart(Game* game, uint32_t uid)
    :  Stage(game, uid)
{

}
StageServerStart::~StageServerStart()
{

}
uint32_t StageServerStart::initialize()
{
    initialized();
    return 0;
}
uint32_t StageServerStart::doRemoteEvent(CommEvent & event)
{
    return 0;
}
uint32_t StageServerStart::doWindowEvent(sf::Event & event)
{
    return 0;
}
uint32_t StageServerStart::doLocalInputs()
{
    return 0;
}
uint32_t StageServerStart::doUpdate()
{
    finished(0);
    return 0;
}
uint32_t StageServerStart::doDraw()
{
    return 0;
}
uint32_t StageServerStart::cleanup()
{
    return 0;
}

uint32_t StageServerStart::processCommands()
{
    return 0;
}


}//end namespace bali
