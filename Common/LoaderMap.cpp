#include "LoaderMap.h"
#include "Map.h"

#include <string>
#include <iostream>
#undef DBG

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
            ASSIGNIFMATCHESSTR("version", map->version);
            ASSIGNIFMATCHESSTR("orientation", map->orientation);
            ASSIGNIFMATCHESINT("width", map->width);
            ASSIGNIFMATCHESINT("height", map->height);
            ASSIGNIFMATCHESINT("tilewidth", map->tilewidth);
            ASSIGNIFMATCHESINT("tileheight", map->tileheight);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "tileset"){
        map->tileSets.push_back(Map::TileSet());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHESINT("firstgid", map->tileSets.back().firstgid);
            ASSIGNIFMATCHESSTR("name", map->tileSets.back().name);
            ASSIGNIFMATCHESINT("tilewidth", map->tileSets.back().tileWidth);
            ASSIGNIFMATCHESINT("tileheight", map->tileSets.back().tileHeight);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }

    }
    else
    if (elementName == "image"){
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHESSTR("source", map->tileSets.back().image.source);
            ASSIGNIFMATCHESSTR("trans", map->tileSets.back().image.trans);
            ASSIGNIFMATCHESINT("width", map->tileSets.back().image.width);
            ASSIGNIFMATCHESINT("height", map->tileSets.back().image.height);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "layer"){
        map->mapLoadState = Map::LAYER;
        map->layers.push_back(Map::Layer());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHESSTR("name", map->layers.back().name);
            ASSIGNIFMATCHESINT("width", map->layers.back().width);
            ASSIGNIFMATCHESINT("height", map->layers.back().height);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "data"){
        map->layers.back().data.push_back(Map::Data());
    }
    else
    if (elementName == "tile"){
        map->layers.back().data.back().tiles.push_back(Map::Tile());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHESINT("gid", map->layers.back().data.back().tiles.back().gid);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "objectgroup"){
        map->mapLoadState = Map::OBJECTGROUP;
        map->objectGroups.push_back(Map::ObjectGroup());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHESSTR("name", map->objectGroups.back().name);
            ASSIGNIFMATCHESINT("width", map->objectGroups.back().width);
            ASSIGNIFMATCHESINT("height", map->objectGroups.back().height);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }

    }
    else
    if (elementName == "property"){
        Map::Property * property = NULL;
        if (map->mapLoadState== Map::MAP){
            map->properties.push_back(Map::Property());
            property = &map->properties.back();
        }
        else
        if (map->mapLoadState == Map::LAYER){
            map->layers.back().properties.push_back(Map::Property());
            property = &map->layers.back().properties.back();
        }
        else
        if (map->mapLoadState == Map::OBJECTGROUP){
            map->objectGroups.back().properties.push_back(Map::Property());
            property = &map->objectGroups.back().properties.back();
        }

        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHESSTR("name", property->name);
            ASSIGNIFMATCHESSTR("value", property->value);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }
    else
    if (elementName == "object"){
        map->objectGroups.back().objects.push_back(Map::Object());
        for (size_t i = 0; attribute[i]; i += 2)
        {
            ASSIGNIFMATCHESINT("x", map->objectGroups.back().objects.back().x);
            ASSIGNIFMATCHESINT("y", map->objectGroups.back().objects.back().y);
            ASSIGNIFMATCHESINT("width", map->objectGroups.back().objects.back().width);
            ASSIGNIFMATCHESINT("height", map->objectGroups.back().objects.back().height);
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
