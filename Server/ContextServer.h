#ifndef ContextServer_h_
#define ContextServer_h_

#include "Comm.h"
#include "ManagerConfiguration.h"
#include "ManagerMap.h"
#include "ManagerWorld.h"
#include "ManagerPlayer.h"

namespace bali{

    class ContextServer{
    public:
        Comm server;

        ManagerConfiguration mc;
        ManagerMap mm;
        ManagerWorld mw;
        ManagerPlayer mp;
    };

}//end namespace bali
#endif


