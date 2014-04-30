#ifndef CompLogicLobby_h_
#define CompLogicLobby_h_

#include "Component.h"

namespace bali{

class CompLogicLobby: public Component
{
public:
    CompLogicLobby();
    ~CompLogicLobby();

    //General Component Functionality
    uint32_t initialize(Context& cc);
    uint32_t doRemoteEvent(Context& cc, CommEvent & event);
    uint32_t doWindowEvent(Context& cc, sf::Event & event);
    uint32_t doLocalInputs(Context& cc);
    uint32_t doUpdate(Context& cc);
    uint32_t doDraw(Context& cc);
    uint32_t cleanup(Context& cc);
    uint32_t processCommands(){}
private:

};
}
#endif


