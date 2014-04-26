#ifndef CommandGame_h_
#define CommandGame_h_

#include "Command.h"

namespace bali{

class CommandGame : public Command
{
public:
    enum class Functions{
        FINISH
    };

    union u{
        struct Finish{

        }f;
    };
};

}//end namespace bali


#endif

