#ifndef CompLogicLobby_h_
#define CompLogicLobby_h_

#include "Component.h"

namespace bali{

class Stage;
class CompLogicLobby: public Component
{
public:
    CompLogicLobby(Stage* stage);
    ~CompLogicLobby();

    //General Component Functionality

    ReturnVal initialize();
    ReturnVal doRemoteEvent(CommEvent & event);
    ReturnVal doWindowEvent(sf::Event & event);
    ReturnVal doLocalInputs();
    ReturnVal doUpdate();
    ReturnVal doDraw();
    ReturnVal cleanup();
    uint32_t processCommands(void* arg);
private:

};
}
#endif


