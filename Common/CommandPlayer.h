#ifndef CommandPlayer_h_
#define CommandPlayer_h_

#include "Command.h"

namespace bali{

class CommandPlayer : public Command
{
public:
    enum class Functions{
        MOVEBEGIN,
        MOVEEND,
        JUMPBEGIN,
        JUMPEND,
        ATTACKBEGIN,
        ATTACKEND,

    };

    union u{

    };
};

}//end namespace bali
#endif

