#ifndef CompDynamicLayer_h_
#define CompDynamicLayer_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"

namespace bali{

class Context;

class CompDynamicLayer : public Component
{
public:
    CompDynamicLayer();
    ~CompDynamicLayer();
    //General Component Functionality
    uint32_t initialize(Context& cc);
    uint32_t doWindowEvent(Context& cc, sf::Event & event);
    uint32_t doLocalInputs(Context& cc);
    uint32_t doUpdate(Context& cc);
    uint32_t doDraw(Context& cc);
    uint32_t cleanup(Context& cc);

private:
    sf::VertexArray layer;
};

}//end namespace bali
#endif

