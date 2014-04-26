#ifndef CommandComponent_h_
#define CommandComponent_h_

#include "Command.h"

namespace bali{

class CommandComponent : public Command
{
public:
    enum class Functions{
        POPULATETEAMLIST,
        PAUSE,
        RESUME,
        SHOW,
        HIDE
    };
    union u{
        struct PopulateTeamList{

        }ptl;
        struct Pause{

        }p;
        struct Resume{

        }r;
        struct Show{

        }s;
        struct Hide{

        }h;
    };
};



}//end namespace bali

#endif

