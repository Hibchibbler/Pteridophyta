#ifndef Command_h_
#define Command_h_

#include <stdint.h>
#include <memory>

namespace bali{

struct Argument
{

};

class Command
{

public:
    typedef std::shared_ptr<Argument> Arg;
    Command(uint32_t f, Arg a)
      : func(f),
        arg(a)

    {

    }

    virtual  ~Command()=default;
    uint32_t  getFunction(){return func;}
    void      setFunction(uint32_t f){func=f;}
    Arg       getArg(){return arg;}
    void      setArg(Arg a){arg=a;}
protected:
    uint32_t  func;
    Arg       arg;
};




}//end namespace bali

#endif

