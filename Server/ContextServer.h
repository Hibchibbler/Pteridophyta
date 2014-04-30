#ifndef ContextServer_h_
#define ContextServer_h_

#include "Context.h"


namespace bali{

    class ContextServer : public Context{
    public:
        uint32_t processCommands(void* arg)
        {
            return 0;
        }
    };

}//end namespace bali
#endif


