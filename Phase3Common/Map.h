#ifndef Map_h_
#define Map_h_

#include "LoaderXML.h"
#include <vector>
#include <string>
namespace bali{


class Image
{
  public:
      std::string source;
      std::string trans;
      std::string width;
      std::string height;
};
class Tileset
{
public:
    std::string name;
    std::string firstgid;
    std::string tilewidth;
    std::string tileheight;
    Image image;
};

class Point
{
public:
    float x;
    float y;
};

class Ellipse
{
public:
};

class Polygon
{
public:
    std::vector<Point> points;
};

class Object
{
public:
    std::string x;
    std::string y;
    std::string width;
    std::string height;
    Ellipse ellipse;
    Polygon polygon;
};

class Tile
{
public:
    std::string gid;
};

class Data
{
public:
    std::vector<Tile> tiles;
};

class MapProperty
{
public:
    std::string name;
    std::string value;
};
class ObjectGroup
{
public:
    std::string name;
    std::string width;
    std::string height;
    std::vector<MapProperty> properties;
    std::vector<Object> objects;
};



class Layer
{
public:
    std::string name;
    std::string width;
    std::string height;

    std::vector<Data> data;
    std::vector<MapProperty> properties;
};

class Map
{
public:
    enum LoadState{
        MAP,
        LAYER,
        OBJECTGROUP
    };
    int mapLoadState;

    std::string version;
    std::string orientation;
    std::string width;
    std::string height;
    std::string tilewidth;
    std::string tileheight;

    std::vector<MapProperty> properties;
    std::vector<Tileset> tileSets;
    std::vector<Layer> layers;
    std::vector<ObjectGroup> objectGroups;

};




}//namespace bali

#endif


