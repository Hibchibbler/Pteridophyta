#ifndef LoaderMap_h_
#define LoaderMap_h_

#include "LoaderXML.h"

//#define DBG

namespace bali{



class ManagerMap;
class LoaderMap : public LoaderXML
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
    LoaderMap();
    ~LoaderMap();
    static bool load(const char *fn, ManagerMap *m);
    static void end_element(void *data, const char *el);
    static void start_element(void *data, const char *element, const char **attribute);

    ///Save
    static bool save(const char *fn, ManagerMap *m);

private:

};


}//namespace bali

#endif

