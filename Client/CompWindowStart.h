#ifndef CompStartWindow_h_
#define CompStartWindow_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"
#include "ReturnVal.h"

namespace bali
{

class Context;

class CompWindowStart : public Component
{
public:
    CompWindowStart(Stage* stage);
    ~CompWindowStart();

    //General Component Functionality
    ReturnVal initialize();
    ReturnVal doWindowEvent(sf::Event & event);
    ReturnVal doLocalInputs();
    ReturnVal doUpdate();
    ReturnVal doDraw();
    ReturnVal cleanup();

    //Commandable obligations
    uint32_t processCommands(void* arg);

    //Specific Component Functionality
    void doStart(Context* ctx);

private:
    sfg::Window::Ptr    window;
    sfg::Desktop        desk;

    sfg::Entry::Ptr   ipEntry;//Kept to retrieve later
    sfg::Entry::Ptr passEntry;//Kept to retrieve later
    sfg::Entry::Ptr portEntry;//Kept to retrieve later
    sfg::Entry::Ptr nameEntry;//Kept to retrieve later

    sf::Clock deskUpdateClock;

};

}//end namespace bali
#endif

