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
    //map = std::make_shared<Map>();

    LoaderMap::load(cm.configuration.global.maps[0].filePath.c_str(), &map);

    //
    //Map::TileSet& ts =
    //cm.configuration.global.maps[i].tileSets[0].load();
    for (auto& t: map.tileSets)
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

uint32_t ManagerMap::getTileSetIndexByGid(uint32_t gid)
{
    //Find the tileset to which this gid refers.
    //iterate through each tileset and check if gid is between the firstgid and lastgid. if so
    //then set tileset as current.
    uint32_t maxTileSetGid=0;

    for (int currentTileSet = 0; currentTileSet < map.tileSets.size(); currentTileSet++)
    {
        uint32_t firstTileSetGid = map.tileSets[currentTileSet].firstgid;
        uint32_t maxTileSetGidW = map.tileSets[currentTileSet].image.width  / map.tileSets[currentTileSet].tileWidth;
        uint32_t maxTileSetGidH = map.tileSets[currentTileSet].image.height / map.tileSets[currentTileSet].tileHeight;
        maxTileSetGid  += maxTileSetGidW*maxTileSetGidH;

        if (firstTileSetGid <= gid && gid <= maxTileSetGid)
        {//t is the tileSet index we want
            return currentTileSet;
        }
    }
    return -1;
}

uint32_t ManagerMap::getFirstNonZeroGidInLayer(uint32_t layer)
{
    for (int j = 0;j < map.layers[layer].data[0].tiles.size();j++)
    {
        if (map.layers[layer].data[0].tiles[j].gid != 0)
        {
            return map.layers[layer].data[0].tiles[j].gid;
        }
    }
    return -1;
}
}//end namespace bali
