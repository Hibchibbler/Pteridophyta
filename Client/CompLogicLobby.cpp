#include "CompLogicLobby.h"
#include "Stage.h"
namespace bali{

CompLogicLobby::CompLogicLobby(Stage* stage)
    : Component(stage)
{
}

CompLogicLobby::~CompLogicLobby()
{
}

//General Component Functionality
uint32_t CompLogicLobby::initialize(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::doRemoteEvent(Context& cc, CommEvent & event)
{

    return 0;
}

uint32_t CompLogicLobby::doWindowEvent(Context& cc, sf::Event & event)
{
    return 0;
}

uint32_t CompLogicLobby::doLocalInputs(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::doUpdate(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::doDraw(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::cleanup(Context& cc)
{
    return 0;
}

uint32_t CompLogicLobby::processCommands(void* arg)
{
    return 0;
}

}
