#ifndef CompStartWindow_h_
#define CompStartWindow_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"


namespace bali
{

class ContextClient;

class CompStartWindow : public Component
{
public:
    CompStartWindow();
    ~CompStartWindow();

    //General Component Functionality
    uint32_t initialize(Context& cc);
    uint32_t doWindowEvent(Context& cc, sf::Event & event);
    uint32_t doLocalInputs(Context& cc);
    uint32_t doUpdate(Context& cc);
    uint32_t doDraw(Context& cc);
    uint32_t cleanup(Context& cc);

    //Specific Component Functionality
    void doStart(ContextClient* cc);
    uint32_t isStarted();
private:
    sfg::Window::Ptr    window;
    sfg::Desktop        desk;

    sfg::Entry::Ptr   ipEntry;//Kept to retrieve later
    sfg::Entry::Ptr passEntry;//Kept to retrieve later
    sfg::Entry::Ptr portEntry;//Kept to retrieve later
    sfg::Entry::Ptr nameEntry;//Kept to retrieve later

    sf::Clock deskUpdateClock;

    uint32_t started=0;
};

}//end namespace bali
#endif

