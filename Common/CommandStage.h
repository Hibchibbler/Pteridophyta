#ifndef CommandStage_h_
#define CommandStage_h_

#include "Command.h"
namespace bali{

class CommandStage : public Command
{
public:

    enum Functions{
        //Client sends, Server recieves
        SENDWHOIS,
        SENDID,
        SENDREADY,

        //Server sends, Client receives
        PROCESSWHOISACK,
        PROCESSIDACK,
        PROCESSIDNACK,

        //General
        STAGEFINISH
    };
//    union {
//        struct {
//            CommEvent event;
//        }ce;
//    }u;
};


}//end namespace bali
#endif


