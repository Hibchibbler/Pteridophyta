#ifndef Component_h_
#define Component_h_
#include <memory>

namespace bali{
class Component;
typedef std::shared_ptr<Component> SComponent;


class Component{
public:

    Component()=default;
    virtual ~Component()=default;

    virtual uint32_t initialize()=0;
    virtual uint32_t doUpdate()=0;
    virtual uint32_t doDraw()=0;
    virtual uint32_t cleanup()=0;
private:
};


}//end namespace bali

#endif

