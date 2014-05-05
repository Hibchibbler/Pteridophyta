#ifndef CommandComponent_h_
#define CommandComponent_h_

#include "Command.h"
#include <vector>
#include <string>


namespace bali{

class CommEvent;
class CommandComponent : public Command
{
public:
    CommandComponent(uint32_t f, Command::Argument::Ptr a);
    enum Functions{
        PAUSE,
        RESUME,
        SHOW,
        HIDE,
        PROCESSDATA,
        PROCESSWHOISACKMSG,
        PROCESSIDACKMSG,
        PROCESSIDNACKMSG,
        PROCESSSTARTMSG
    };

    struct WhoIsAckStruct : public Command::Argument{
        struct NameTeam{
            NameTeam(std::string n, uint32_t t){
                name=n;
                team=t;
            }
            std::string name;
            uint32_t team;
        };
        std::vector<NameTeam> names;
    };
    struct IdAckStruct : public Command::Argument{
        std::string mapName;
    };

    static
    Command::Argument::Ptr structifyWhoIsAck(CommEvent& event);

    static
    Command::Argument::Ptr structifyIdAck(CommEvent& event);

};



}//end namespace bali

#endif

