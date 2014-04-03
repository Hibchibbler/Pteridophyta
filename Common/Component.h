#ifndef Component_h_
#define Component_h_


#include <memory>


namespace bali{

class StageClientStart;
class ContextClient;

class Component{
public:

    Component()=default;
    virtual ~Component()=default;

    virtual uint32_t initialize(ContextClient& cc)=0;
    virtual uint32_t doWindowEvents(ContextClient& cc, sf::Event & event)=0;
    virtual uint32_t doLocalInputs(ContextClient& cc)=0;
    virtual uint32_t doUpdate(ContextClient& cc)=0;
    virtual uint32_t doDraw(ContextClient& cc)=0;
    virtual uint32_t cleanup(ContextClient& cc)=0;

    uint32_t setVisible(uint32_t v){return (visible = v);}
    uint32_t getVisible(){return visible;}

    ///getError(); if returns > 0 then error
    uint32_t setError(uint32_t e){err = e;}
    uint32_t getError(){return err;}

    uint32_t err=0;
    uint32_t visible=1;
private:
};
typedef std::shared_ptr<Component> SComponent;

}//end namespace bali

#endif

