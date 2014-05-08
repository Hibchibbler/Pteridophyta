#include "ManagerMap.h"
#include "LoaderMap.h"
#include "ManagerConfiguration.h"
#include "Util.h"

#include <iostream>
#include <map>
namespace bali{


ManagerMap::ManagerMap(){

}

ManagerMap::~ManagerMap(){

}

bool ManagerMap::initialize(ManagerConfiguration& cm){

    //There should only be 1 iteration
    if (cm.global.maps.size() > 1)
    {
        std::cout << "WARNING; configuration.xml; Found two <map> elements. NOT SUPPORTED." << std::endl;
        return false;
    }


    std::cout << "Loading Map " << cm.global.maps[0].filePath.c_str() << std::endl;
    //map = std::make_shared<Map>();

    LoaderMap::load(cm.global.maps[0].filePath.c_str(), this);

    //
    //Map::TileSet& ts =
    //cm.global.maps[i].tileSets[0].load();
    for (auto& t: tileSets)
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

uint32_t ManagerMap::initializeLayer(uint32_t layer, sf::VertexArray& newLayer)
{
    //N.B. - assuming width == height in a lot of places
    //ContextClient&              cc              = g->ctx;
    //ManagerMap&                 mm              = cc.mm;
    //Map&                        map             = mm.map;
    std::vector<ManagerMap::Tile>&     tiles           = layers[layer].data[0].tiles;
    uint32_t                    mapWidth        = width;
    int                         numTileSets     = tileSets.size();

    for (int index = 0; index < tiles.size();index++)
    {
        //current gid
        uint32_t gid = tiles[index].gid;
        if (gid == 0)
            continue;

        //Find the tileset to which this gid refers. - gid MUST be valid
        uint32_t currentTileSet  = getTileSetIndexByGid(gid);

        //Get all the things we need from this tileset.
        uint32_t firstGid        = tileSets[currentTileSet].firstgid;

        uint32_t tileWidth       = tileSets[currentTileSet].tileWidth;
        uint32_t tileHeight      = tileSets[currentTileSet].tileHeight;

        uint32_t imageWidth      = tileSets[currentTileSet].image.width;
        uint32_t imageHeight     = tileSets[currentTileSet].image.height;

        //This converts a global id to a local id.
        uint32_t lid             = gid - firstGid;

        //This is where we map the current gid to the upper left corner of a region in a sprite sheet.
        //Convert current gid to the upper left corner(x,y) of a sub rect that represents a particular sprite.
        sf::Vector2i pos;
        pos = indexToPosition(lid,  imageWidth, tileWidth,tileHeight);//parameter 4 is how many tiles wide the sprite sheet is.

        //Then, Set the sub rect for the sprite
        tileSets[currentTileSet].sprite.setTextureRect(sf::IntRect(pos.x,pos.y,tileWidth,tileHeight));

        //This is where we use the implied position in an array to map to a screen position.
        //Convert index to the upper left corner(x,y) of a tile sized region on the screen.
        //Index represents the implied position of the tile in the tiles vector.
        //In a TMX file, there is <Layer><Data><Tile><Tile>...<Tile></Data></Layer>
        pos = indexToPosition(index, mapWidth, tileWidth, tileHeight);//parameter 4 is how many tiles wide the map is.


        //Add a quad the size of a tile. and specify the texture coordinates using the sub rect specified earlier.
        addStraightQuad(newLayer, sf::FloatRect((float)pos.x,(float)pos.y, tileWidth,tileHeight), tileSets[currentTileSet].sprite.getTextureRect());
    }
    return 0;
}

uint32_t ManagerMap::getTileSetIndexByGid(uint32_t gid)
{
    //Find the tileset to which this gid refers.
    //iterate through each tileset and check if gid is between the firstgid and lastgid. if so
    //then set tileset as current.
    uint32_t maxTileSetGid=0;

    for (int currentTileSet = 0; currentTileSet < tileSets.size(); currentTileSet++)
    {
        uint32_t firstTileSetGid = tileSets[currentTileSet].firstgid;
        uint32_t maxTileSetGidW = tileSets[currentTileSet].image.width  / tileSets[currentTileSet].tileWidth;
        uint32_t maxTileSetGidH = tileSets[currentTileSet].image.height / tileSets[currentTileSet].tileHeight;
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
    for (int j = 0;j < layers[layer].data[0].tiles.size();j++)
    {
        if (layers[layer].data[0].tiles[j].gid != 0)
        {
            return layers[layer].data[0].tiles[j].gid;
        }
    }
    return -1;
}
}//end namespace bali

