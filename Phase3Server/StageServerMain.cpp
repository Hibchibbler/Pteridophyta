#include "StageServerMain.h"
StageServerMain::StageServerMain(Game & game, sf::Uint32 uid)
    :  GameStage(game, uid)
{

}
StageServerMain::~StageServerMain()
{

}
sf::Uint32 StageServerMain::initialize()
{
    initialized();
    return 0;
}
sf::Uint32 StageServerMain::doRemoteEvents(CommEvent & cevent)
{
    return 0;
}
sf::Uint32 StageServerMain::doWindowEvents(sf::Event & wevent)
{
    return 0;
}
sf::Uint32 StageServerMain::doLocalInputs()
{
    return 0;
}
sf::Uint32 StageServerMain::doLoop()
{
    finished(0);
    return 0;
}
sf::Uint32 StageServerMain::doDraw()
{
    return 0;
}
sf::Uint32 StageServerMain::cleanup()
{
    return 0;
}

