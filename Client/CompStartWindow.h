#ifndef CompStartWindow_h_
#define CompStartWindow_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"


namespace bali
{

class CompStartWindow : public Component
{
public:
    CompStartWindow();
    ~CompStartWindow();
    uint32_t initialize(ContextClient& cc);
    uint32_t doWindowEvents(ContextClient& cc, sf::Event & event);
    uint32_t doLocalInputs(ContextClient& cc);
    uint32_t doUpdate(ContextClient& cc);
    uint32_t doDraw(ContextClient& cc);
    uint32_t cleanup(ContextClient& cc);
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

