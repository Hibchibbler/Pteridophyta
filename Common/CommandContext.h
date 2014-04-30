#ifndef CommandContext_h_
#define CommandContext_h_

#include "Command.h"

namespace bali{

class CommandContext : public Command
{
public:
    enum class Functions{
        SETIDENTITY,
        SETREADY,


    };
private:

};



}//end namespace bali


#endif



