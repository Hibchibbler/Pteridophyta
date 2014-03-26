#include "ManagerMap.h"
#include "LoaderMap.h"
#include "ManagerConfiguration.h"
#include "Map.h"
#include <iostream>
namespace bali{


ManagerMap::ManagerMap(){

}

ManagerMap::~ManagerMap(){

}

bool ManagerMap::initialize(ManagerConfiguration& cm){

    //There should only be 1 iteration
    if (cm.configuration.global.maps.size() > 1)
    {
        std::cout << "WARNING; configuration.xml; Found two <map> elements. NOT SUPPORTED." << std::endl;
        return false;
    }


    std::cout << "Loading Map " << cm.configuration.global.maps[0].filePath.c_str() << std::endl;
    map = std::make_shared<Map>();

    LoaderMap::load(cm.configuration.global.maps[0].filePath.c_str(), map.get());

    //
    //Map::TileSet& ts =
    //cm.configuration.global.maps[i].tileSets[0].load();
    for (auto& t: map->tileSets)
    {   std::cout << "loading tileset" << std::endl;
        t.load();
    }


    return true;
}

bool ManagerMap::update(){

    return true;
}

bool ManagerMap::cleanup(){

    return true;
}



}//end namespace bali
