#ifndef Commandable_h_
#define Commandable_h_

#include <vector>

namespace bali{

template <typename T>
class Commandable
{
public:
    virtual ~Commandable(){};
    void submitCommand(T& cmd){
        commands.push_back(cmd);
    }
    virtual uint32_t processCommands()=0;
protected:
    std::vector<T> commands;
};

}//end namespace bali

#endif
