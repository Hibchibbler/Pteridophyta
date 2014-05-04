#ifndef CommandStage_h_
#define CommandStage_h_

#include "Command.h"
namespace bali{

class CommandStage : public Command
{
public:
    CommandStage(uint32_t f, Command::Arg  a)
        : Command(f,a){}

    enum Functions{
        //Client sends, Server recieves
        SENDWHOIS,
        SENDID,
        SENDREADY,

        //General
        STAGEFINISH
    };

};


}//end namespace bali
#endif


