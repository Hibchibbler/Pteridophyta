#ifndef Map_h_
#define Map_h_

#include "LoaderXML.h"
#include <vector>
#include <string>
namespace bali{




class Map
{
public:
    struct Image
    {
        std::string             source;
        std::string             trans;
        std::string             width;
        std::string             height;
    };
    struct Tileset
    {
        std::string             name;
        std::string             firstgid;
        std::string             tileWidth;
        std::string             tileHeight;
        Image                   image;
    };

    struct Point
    {
        float x;
        float y;
    };

    struct Ellipse
    {
    };

    struct Polygon
    {
        std::vector<Point>      points;
    };

    struct Object
    {
        std::string             x;
        std::string             y;
        std::string             width;
        std::string             height;
        Ellipse                 ellipse;
        Polygon                 polygon;
    };

    struct Tile
    {
        std::string             gid;
    };

    struct Data
    {
        std::vector<Tile>       tiles;
    };

    struct Property
    {
        std::string name;
        std::string value;
    };
    struct ObjectGroup
    {
        std::string             name;
        std::string             width;
        std::string             height;
        std::vector<Property>   properties;
        std::vector<Object>     objects;
    };



    struct Layer
    {
        std::string             name;
        std::string             width;
        std::string             height;

        std::vector<Data>       data;
        std::vector<Property>   properties;
    };
    enum LoadState{
        MAP,
        LAYER,
        OBJECTGROUP
    };
    int mapLoadState;

    std::string                 version;
    std::string                 orientation;
    std::string                 width;
    std::string                 height;
    std::string                 tilewidth;
    std::string                 tileheight;

    std::vector<Property>       properties;
    std::vector<Tileset>        tileSets;
    std::vector<Layer>          layers;
    std::vector<ObjectGroup>    objectGroups;

};




}//namespace bali

#endif


