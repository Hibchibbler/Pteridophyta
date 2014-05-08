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
    uint32_t initialize(Context& ctx);
    uint32_t doRemoteEvent(Context& ctx, CommEvent & event);
    uint32_t doWindowEvent(Context& ctx, sf::Event & event);
    uint32_t doLocalInputs(Context& ctx);
    uint32_t doUpdate(Context& ctx);
    uint32_t doDraw(Context& ctx);
    uint32_t cleanup(Context& ctx);
    uint32_t processCommands(void* arg);
private:

};
}
#endif


