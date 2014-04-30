#ifndef Commandable_h_
#define Commandable_h_

#include <vector>

namespace bali{

template <typename T>
class Commandable
{
public:
    virtual ~Commandable(){};
    virtual void submitCommand(T& cmd){
        commands.push_back(cmd);
    }
    virtual void submitCommand(Commandable* c, T& cmd){
        c->submitCommand(cmd);
    }
    virtual uint32_t processCommands(void* arg)=0;
    virtual uint32_t isCommandSupported(uint32_t function){return 0;}
protected:
    std::vector<T> commands;
};

}//end namespace bali

#endif
