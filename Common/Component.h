#ifndef Component_h_
#define Component_h_


#include <memory>


namespace bali{


class Context;
//The Component class establishes an interface that is natural to the core flow.
//A component is meant to represent a single function within a Stage.
//Usually a component will have specific functions that are not general. that is ok
//because the interface that Component specifies is still considerably useful.
class Component{
public:

    Component()=default;
    virtual ~Component()=default;

    virtual uint32_t initialize(Context& cc)=0;
    virtual uint32_t doWindowEvent(Context& cc, sf::Event & event)=0;
    virtual uint32_t doLocalInputs(Context& cc)=0;
    virtual uint32_t doUpdate(Context& cc)=0;
    virtual uint32_t doDraw(Context& cc)=0;
    virtual uint32_t cleanup(Context& cc)=0;

    uint32_t setVisible(uint32_t v){return (visible = v);}
    uint32_t getVisible(){return visible;}

    ///getError(); if returns > 0 then error
    uint32_t setError(uint32_t e){err = e;return e;}
    uint32_t getError(){return err;}

    uint32_t err=0;
    uint32_t visible=1;
private:
};
typedef std::shared_ptr<Component> SComponent;

}//end namespace bali

#endif

