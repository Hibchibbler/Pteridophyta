#ifndef Command_h_
#define Command_h_

#include <stdint.h>
#include <memory>

namespace bali{



class Command
{
public:
    struct Argument
    {
        typedef std::shared_ptr<Argument> Ptr;
    };

    typedef std::shared_ptr<Command> Ptr;

    Command(uint32_t f, Argument::Ptr a)
      : func(f),
        arg(a)
    {
    }

    virtual  ~Command()=default;
    uint32_t  getFunction(){return func;}
    void      setFunction(uint32_t f){func=f;}
    Argument::Ptr       getArg(){return arg;}
    void      setArg(Argument::Ptr a){arg=a;}
protected:
    uint32_t  func;
    Argument::Ptr       arg;
};





}//end namespace bali

#endif

