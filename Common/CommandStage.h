#ifndef CommandStage_h_
#define CommandStage_h_

#include "Command.h"
namespace bali{

class CommandStage : public Command
{
public:
    enum Functions{
//        WHOIS,
//        WHOISACK,
//        ID,
//        IDACK,
//        IDNACK,
//        START,
//        READY,
        UPDATECLIENT,
        TRANSITION
    };
};


}//end namespace bali
#endif


