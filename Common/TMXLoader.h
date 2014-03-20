
#ifndef tmxloader_h_
#define tmxloader_h_


#include <string.h>
#include <iostream>


#include "XMLLoader.h"


using namespace std;

namespace bali{
namespace tmx{
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

class Property
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
    std::vector<Property> properties;
    std::vector<Object> objects;
};



class Layer
{
public:
    std::string name;
    std::string width;
    std::string height;

    std::vector<Data> data;
    std::vector<Property> properties;
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

    std::vector<Property> properties;
    std::vector<Tileset> tileSets;
    std::vector<Layer> layers;
    std::vector<ObjectGroup> objectGroups;

};

class TMXLoader : public XMLLoader
{
public:
/*
//    tiled tmx file structure
//
//        MAP_OPEN,
//            TILESET_OPEN,
//                IMAGE_OPEN,
//                IMAGE_CLOSE,
//            TILESET_CLOSE,
//            ...
//            LAYER_OPEN,
//                PROPERTIES_OPEN,
//                    PROPERTY_OPEN,
//                    PROPERTY_CLOSE,
//                    ...
//                PROPERTIES_CLOSE,
//                DATA_OPEN,
//                    TILE_OPEN,
//                    TILE_CLOSE,
//                    ...
//                DATA_CLOSE,
//            LAYER_CLOSE,
//            ...
//            OBJECTGROUP_OPEN,
//                PROPERTIES_OPEN,
//                    PROPERTY_OPEN,
//                    PROPERTY_CLOSE,
//                    ...
//                PROPERTIES_CLOSE,
//                OBJECT_OPEN,
//                    POLYGON_OPEN,
//                    POLYGON_CLOSE,
//                    ELLIPSE_OPEN,
//                    ELLIPSE_CLOSE,
//                OBJECT_CLOSE,
//                ...
//            OBJECTGROUP_CLOSE,
//            ...
//        MAP_CLOSE
*/



    TMXLoader(){
    }


    ~TMXLoader(){
    }

    static bool load(char *fn, Map *m){
        return XMLLoader::load(fn, m, TMXLoader::start_element, TMXLoader::end_element);
    }

    static void end_element(void *data, const char *el){
        //Debug
        cout << "</"<<el << ">" << endl;
        ///////
    }
    static void start_element(void *data, const char *element, const char **attribute){

        //Debug
        cout << "<" << element << ">"<< endl;
        for (size_t i = 0; attribute[i]; i += 2){
            cout << "\t" << attribute[i]<< "=" << attribute[i+1]<< endl;
        }
        ///////
        //TMXLoader *loader = ((TMXLoader*)data);
        Map       *map    = (Map*)data;

        std::string elementName(element);
        if (elementName == "map"){
            map->mapLoadState = Map::MAP;
            for (size_t i = 0; attribute[i]; i += 2)
            {
                assignIfMatches("version", map->version);
                assignIfMatches("orientation", map->orientation);
                assignIfMatches("width", map->width);
                assignIfMatches("height", map->height);
                assignIfMatches("tilewidth", map->tilewidth);
                assignIfMatches("tileheight", map->tileheight);
                cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << endl;
            }
        }
        else
        if (elementName == "tileset"){
            map->tileSets.push_back(Tileset());
            for (size_t i = 0; attribute[i]; i += 2)
            {
                assignIfMatches("firstgid", map->tileSets.back().firstgid);
                assignIfMatches("name", map->tileSets.back().name);
                assignIfMatches("tilewidth", map->tileSets.back().tilewidth);
                assignIfMatches("tileheight", map->tileSets.back().tileheight);
                cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << endl;
            }

        }
        else
        if (elementName == "image"){
            for (size_t i = 0; attribute[i]; i += 2)
            {
                assignIfMatches("source", map->tileSets.back().image.source);
                assignIfMatches("trans", map->tileSets.back().image.trans);
                assignIfMatches("width", map->tileSets.back().image.width);
                assignIfMatches("height", map->tileSets.back().image.height);
                cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << endl;
            }
        }
        else
        if (elementName == "layer"){
            map->mapLoadState = Map::LAYER;
            map->layers.push_back(Layer());
            for (size_t i = 0; attribute[i]; i += 2)
            {
                assignIfMatches("name", map->layers.back().name);
                assignIfMatches("width", map->layers.back().width);
                assignIfMatches("height", map->layers.back().height);
                cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << endl;
            }
        }
        else
        if (elementName == "data"){
            map->layers.back().data.push_back(Data());
        }
        else
        if (elementName == "tile"){
            map->layers.back().data.back().tiles.push_back(Tile());
            for (size_t i = 0; attribute[i]; i += 2)
            {
                assignIfMatches("gid", map->layers.back().data.back().tiles.back().gid);
                cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << endl;
            }
        }
        else
        if (elementName == "objectgroup"){
            map->mapLoadState = Map::OBJECTGROUP;
            map->objectGroups.push_back(ObjectGroup());
            for (size_t i = 0; attribute[i]; i += 2)
            {
                assignIfMatches("name", map->objectGroups.back().name);
                assignIfMatches("width", map->objectGroups.back().width);
                assignIfMatches("height", map->objectGroups.back().height);
                cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << endl;
            }

        }
        else
        if (elementName == "property"){
            Property * property = NULL;
            if (map->mapLoadState== Map::MAP){
                map->properties.push_back(Property());
                property = &map->properties.back();
            }
            else
            if (map->mapLoadState == Map::LAYER){
                map->layers.back().properties.push_back(Property());
                property = &map->layers.back().properties.back();
            }
            else
            if (map->mapLoadState == Map::OBJECTGROUP){
                map->objectGroups.back().properties.push_back(Property());
                property = &map->objectGroups.back().properties.back();
            }

            for (size_t i = 0; attribute[i]; i += 2)
            {
                assignIfMatches("name", property->name);
                assignIfMatches("value", property->value);
                cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << endl;
            }
        }
        else
        if (elementName == "object"){
            map->objectGroups.back().objects.push_back(Object());
            for (size_t i = 0; attribute[i]; i += 2)
            {
                assignIfMatches("x", map->objectGroups.back().objects.back().x);
                assignIfMatches("y", map->objectGroups.back().objects.back().y);
                assignIfMatches("width", map->objectGroups.back().objects.back().width);
                assignIfMatches("height", map->objectGroups.back().objects.back().height);
                cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << endl;
            }
        }else{
                cout << "ignoring " << elementName << endl;
        }
    }

    ///Save
    static bool save(Map *m, const char *fn){
//        const char * xmlStart = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
//        ofstream fout(fn);
//        if (!fout.is_open())
//            return false;
//
//        fout.writeline(xmlStart, strlen(xmlStart));
        return false;
    }

private:

};

}//namespace tmx
}//namespace bali

#endif

