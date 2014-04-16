#ifndef Context_h_
#define Context_h_

#include "Comm.h"
#include "ManagerTile.h"
#include "ManagerConfiguration.h"
#include "ManagerMap.h"
#include "ManagerWorld.h"
#include "ManagerPlayer.h"

namespace bali{

///This class is the primary interface to change game state, and to get game state.
class Context
{
public:
    Comm net;
    ManagerConfiguration mc;
    ManagerMap mm;
    ManagerTile mt;
    ManagerWorld mw;
    ManagerPlayer mp;


};

}//end namespace bali
#endif

