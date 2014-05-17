#ifndef Component_h_
#define Component_h_

#include "Commandable.h"
#include "CommandComponent.h"

#include <memory>
#include <SFML\Window\Event.hpp>
#include "ReturnVal.h"

namespace bali{


class CommEvent;
class Command;
class Context;
class Stage;
//The Component class establishes an interface that is natural to the core flow.
//A component is meant to represent a single function within a Stage.
//Usually a component will have specific functions that are not general. that is ok
//because the interface that Component specifies is still considerably useful.
//HUD, MiniMap, Main Game Screen, etc.. are examples of a Component
class Component : public Commandable
{
public:

    Component(Stage* stage) : stage(stage){}
    virtual ~Component(){};

    virtual ReturnVal initialize()=0;
    virtual ReturnVal doRemoteEvent(CommEvent& event){return ReturnVal();}
    virtual ReturnVal doWindowEvent(sf::Event & event){return ReturnVal();}
    virtual ReturnVal doLocalInputs(){return ReturnVal();};
    virtual ReturnVal doUpdate(){return ReturnVal();};
    virtual ReturnVal doDraw(){return ReturnVal();};
    virtual ReturnVal cleanup()=0;

    uint32_t setVisible(uint32_t v){return (visible = v);}
    uint32_t getVisible(){return visible;}

    ///getError(); if returns > 0 then error
    uint32_t setError(uint32_t e){err = e;return e;}
    uint32_t getError(){return err;}

    uint32_t err=0;
    uint32_t visible=1;

    Stage* stage;

    //Commandable obligation
    //uint32_t processCommands(void* arg){}

private:
};


}//end namespace bali

#endif

