#ifndef MapManager_h_
#define MapManager_h_

#include "Map.h"
#include <memory>


namespace bali{


class ManagerConfiguration;
class ManagerMap{
public:
    typedef std::vector<std::unique_ptr<Map> > Maps;

    ManagerMap();
    ~ManagerMap();
    bool initialize(ManagerConfiguration& cm);
    bool update();
    bool cleanup();


    Maps maps;
};




}//end namespace bali
#endif

