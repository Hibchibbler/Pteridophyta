#ifndef Commandable_h_
#define Commandable_h_

#include <vector>
#include <memory>

namespace bali{

class Command;
class Commandable
{
public:
    virtual ~Commandable(){};
    virtual void submitCommand(std::shared_ptr<Command> cmd)
    {
        commands.push_back(cmd);
    }
    virtual uint32_t processCommands(void* arg)=0;
protected:
    std::vector<std::shared_ptr<Command> > commands;
};

}//end namespace bali

#endif
