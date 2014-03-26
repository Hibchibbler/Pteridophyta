#ifndef Map_h_
#define Map_h_

#include "LoaderXML.h"
#include <SFML\graphics.hpp>
#include <vector>
#include <string>
namespace bali{




class Map
{
public:


    class TileSet
    {
    public:
        struct Image
        {
            std::string             source;
            std::string             trans;
            uint32_t                width;
            uint32_t                height;
        };
        uint32_t load(){
            img.loadFromFile(image.source);
            img.createMaskFromColor(sf::Color::Cyan,0);
            tex.loadFromImage(img);
            tex.setSmooth(false);
            sprite.setTexture(tex);
            return 0;
        }
        uint32_t unload(){
            return 0;
        }
        sf::Image               img;
        sf::Texture             tex;
        sf::Sprite              sprite;

        std::string             name;
        uint32_t                firstgid;
        uint32_t                tileWidth;
        uint32_t                tileHeight;
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
        uint32_t                x;
        uint32_t                y;
        uint32_t                width;
        uint32_t                height;
        Ellipse                 ellipse;
        Polygon                 polygon;
    };

    struct Tile
    {
        uint32_t                gid;
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
        uint32_t                width;
        uint32_t                height;
        std::vector<Property>   properties;
        std::vector<Object>     objects;
    };



    struct Layer
    {
        std::string             name;
        uint32_t                width;
        uint32_t                height;

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
    uint32_t                    width;
    uint32_t                    height;
    uint32_t                    tilewidth;
    uint32_t                    tileheight;

    std::vector<Property>       properties;
    std::vector<TileSet>        tileSets;
    std::vector<Layer>          layers;
    std::vector<ObjectGroup>    objectGroups;

};




}//namespace bali

#endif


