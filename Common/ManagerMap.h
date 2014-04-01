#ifndef MapManager_h_
#define MapManager_h_

#include "Map.h"
#include <memory>
#include <map>


namespace bali{


class ManagerConfiguration;
class ManagerMap{
public:
    //typedef std::map<std::string, std::shared_ptr<Map> > Maps;

    ManagerMap();
    ~ManagerMap();
    bool initialize(ManagerConfiguration& cm);
    bool update();
    bool cleanup();


    uint32_t getTileSetIndexByGid(uint32_t gid);
    uint32_t getFirstNonZeroGidInLayer(uint32_t layer);
    //Maps maps;
    std::shared_ptr<Map> map;
};




}//end namespace bali
#endif

