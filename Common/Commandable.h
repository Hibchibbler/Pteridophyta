#ifndef Commandable_h_
#define Commandable_h_

#include <vector>

namespace bali{

//template <typename T>
class Command;
class Commandable
{
public:
    typedef std::shared_ptr<Command> shCommand;
    virtual ~Commandable(){};
    virtual void submitCommand(std::shared_ptr<Command> cmd){
        commands.push_back(cmd);
    }
    virtual uint32_t processCommands(void* arg)=0;
    virtual uint32_t isCommandSupported(uint32_t function){return 0;}
protected:
    std::vector<std::shared_ptr<Command>> commands;
};

}//end namespace bali

#endif
