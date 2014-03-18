#include "LoaderMap.h"
#include "Map.h"

#include <string>
#include <iostream>
#define DBG

namespace bali{


LoaderMap::LoaderMap(){
}


LoaderMap::~LoaderMap(){
}

bool LoaderMap::load(const char *fn, Map *m){
    return LoaderXML::load(fn, m, LoaderMap::start_element, LoaderMap::end_element);
}

void LoaderMap::end_element(void *data, const char *el){
#ifdef DBG
    std::cout << "</"<<el << ">" << std::endl;
#endif
}
void LoaderMap::start_element(void *data, const char *element, const char **attribute){


#ifdef DBG
    std::cout << "<" << element << ">"<< std::endl;
    for (size_t i = 0; attribute[i]; i += 2){
        std::cout << "\t" << attribute[i]<< "=" << attribute[i+1]<< std::endl;
    }
#endif
    ///////
    Map       *map    = (Map*)data;

    std::string elementName(element);
    if (elementName == "map"){
        map->mapLoadState = Map::MAP;
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHES("version", map->version);
            ASSIGNIFMATCHES("orientation", map->orientation);
            ASSIGNIFMATCHES("width", map->width);
            ASSIGNIFMATCHES("height", map->height);
            ASSIGNIFMATCHES("tilewidth", map->tilewidth);
            ASSIGNIFMATCHES("tileheight", map->tileheight);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "tileset"){
        map->tileSets.push_back(Tileset());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHES("firstgid", map->tileSets.back().firstgid);
            ASSIGNIFMATCHES("name", map->tileSets.back().name);
            ASSIGNIFMATCHES("tilewidth", map->tileSets.back().tilewidth);
            ASSIGNIFMATCHES("tileheight", map->tileSets.back().tileheight);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }

    }
    else
    if (elementName == "image"){
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHES("source", map->tileSets.back().image.source);
            ASSIGNIFMATCHES("trans", map->tileSets.back().image.trans);
            ASSIGNIFMATCHES("width", map->tileSets.back().image.width);
            ASSIGNIFMATCHES("height", map->tileSets.back().image.height);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "layer"){
        map->mapLoadState = Map::LAYER;
        map->layers.push_back(Layer());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHES("name", map->layers.back().name);
            ASSIGNIFMATCHES("width", map->layers.back().width);
            ASSIGNIFMATCHES("height", map->layers.back().height);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
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
            ASSIGNIFMATCHES("gid", map->layers.back().data.back().tiles.back().gid);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "objectgroup"){
        map->mapLoadState = Map::OBJECTGROUP;
        map->objectGroups.push_back(ObjectGroup());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHES("name", map->objectGroups.back().name);
            ASSIGNIFMATCHES("width", map->objectGroups.back().width);
            ASSIGNIFMATCHES("height", map->objectGroups.back().height);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }

    }
    else
    if (elementName == "property"){
        MapProperty * property = NULL;
        if (map->mapLoadState== Map::MAP){
            map->properties.push_back(MapProperty());
            property = &map->properties.back();
        }
        else
        if (map->mapLoadState == Map::LAYER){
            map->layers.back().properties.push_back(MapProperty());
            property = &map->layers.back().properties.back();
        }
        else
        if (map->mapLoadState == Map::OBJECTGROUP){
            map->objectGroups.back().properties.push_back(MapProperty());
            property = &map->objectGroups.back().properties.back();
        }

        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHES("name", property->name);
            ASSIGNIFMATCHES("value", property->value);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "object"){
        map->objectGroups.back().objects.push_back(Object());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHES("x", map->objectGroups.back().objects.back().x);
            ASSIGNIFMATCHES("y", map->objectGroups.back().objects.back().y);
            ASSIGNIFMATCHES("width", map->objectGroups.back().objects.back().width);
            ASSIGNIFMATCHES("height", map->objectGroups.back().objects.back().height);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }else{
            std::cout << "Ignoring Element " << elementName << std::endl;
    }
    int a = 42;
}

///Save
bool LoaderMap::save(const char *fn, Map *m){
//        const char * xmlStart = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
//        ofstream fout(fn);
//        if (!fout.is_open())
//            return false;
//
//        fout.writeline(xmlStart, strlen(xmlStart));
    return false;
}


}//end namespace bali
