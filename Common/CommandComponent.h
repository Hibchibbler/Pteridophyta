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
    CommandComponent(uint32_t f, Command::Arg a);
    enum Functions{
        PAUSE,
        RESUME,
        SHOW,
        HIDE,
        PROCESSWHOISACKMSG,
        PROCESSIDACKMSG,
        PROCESSIDNACKMSG,
        PROCESSSTARTMSG
    };

    struct WhoIsAckStruct : public Argument{
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
    struct IdAckStruct : public Argument{
        std::string mapName;
    };

    static
    Command::Arg structifyWhoIsAck(CommEvent& event);

    static
    Command::Arg structifyIdAck(CommEvent& event);

};



}//end namespace bali

#endif

