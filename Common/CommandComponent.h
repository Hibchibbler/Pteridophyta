#ifndef CommandComponent_h_
#define CommandComponent_h_

#include "Command.h"

namespace bali{

class CommandComponent : public Command
{
public:
    enum Functions{
        POPULATETEAMLIST,
        PAUSE,
        RESUME,
        SHOW,
        HIDE,
        GOTWHOISACK,
        GOTID,
        GOTIDACK,
        GOTIDNACK,
        GOTSTART,
        PROCESSWHOISACKMSG,
        PROCESSIDACKMSG,
        PROCESSIDNACKMSG,
        PROCESSSTARTMSG

    };
    const uint32_t MAX_NAMES = 10;
    union arg{
        struct ProcessWhoIsAckMsg{
            std::string names[MAX_NAMES];
        }pwiam;

    };
};



}//end namespace bali

#endif

