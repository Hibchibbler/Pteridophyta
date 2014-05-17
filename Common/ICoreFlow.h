#ifndef ICoreFlow_h_
#define ICoreFlow_h_

#include "ReturnVal.h"
#include <SFML\Window.hpp>

namespace bali{

class CommEvent;

class ICoreFlow
{
public:
    virtual ReturnVal initialize()=0;
    virtual ReturnVal doRemoteEvent(CommEvent & event)=0;
    virtual ReturnVal doWindowEvent(sf::Event & event)=0;
    virtual ReturnVal doLocalInputs()=0;
    virtual ReturnVal doUpdate()=0;
    virtual ReturnVal doDraw()=0;
    virtual ReturnVal cleanup()=0;
};

}

#endif

