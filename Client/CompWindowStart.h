#ifndef CompStartWindow_h_
#define CompStartWindow_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"


namespace bali
{

class ContextClient;

class CompWindowStart : public Component
{
public:
    CompWindowStart(Stage* stage);
    ~CompWindowStart();

    //General Component Functionality
    uint32_t initialize(Context& c);
    uint32_t doWindowEvent(Context& c, sf::Event & event);
    uint32_t doLocalInputs(Context& c);
    uint32_t doUpdate(Context& c);
    uint32_t doDraw(Context& c);
    uint32_t cleanup(Context& c);

    //Commandable obligations
    uint32_t processCommands(void* arg);

    //Specific Component Functionality
    void doStart(ContextClient* cc);

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

