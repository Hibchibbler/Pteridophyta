#include "StageServerStart.h"

namespace bali{

StageServerStart::StageServerStart(Game & game, sf::Uint32 uid)
    :  GameStage(game, uid)
{

}
StageServerStart::~StageServerStart()
{

}
sf::Uint32 StageServerStart::initialize()
{
    initialized();
    return 0;
}
sf::Uint32 StageServerStart::doRemoteEvents(CommEvent & cevent)
{
    return 0;
}
sf::Uint32 StageServerStart::doWindowEvents(sf::Event & wevent)
{
    return 0;
}
sf::Uint32 StageServerStart::doLocalInputs()
{
    return 0;
}
sf::Uint32 StageServerStart::doLoop()
{
    finished(0);
    return 0;
}
sf::Uint32 StageServerStart::doDraw()
{
    return 0;
}
sf::Uint32 StageServerStart::cleanup()
{
    return 0;
}

}//end namespace bali
