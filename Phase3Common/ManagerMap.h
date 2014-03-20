#ifndef MapManager_h_
#define MapManager_h_

#include "Map.h"
#include <memory>
#include <map>


namespace bali{


class ManagerConfiguration;
class ManagerMap{
public:
    typedef std::map<std::string, std::unique_ptr<Map> > Maps;

    ManagerMap();
    ~ManagerMap();
    bool initialize(ManagerConfiguration& cm);
    bool update();
    bool cleanup();


    Maps maps;
};




}//end namespace bali
#endif

