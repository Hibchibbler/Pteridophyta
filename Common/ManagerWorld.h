#ifndef ManagerWorld_h_
#define ManagerWorld_h_

namespace bali{

class ManagerConfiguration;
class ManagerMap;
class ManagerWorld{
public:
    bool initialize(ManagerConfiguration& configMan, ManagerMap& mapMan);
    bool update();
    bool cleanup();
};


}//end namespace bali

#endif


