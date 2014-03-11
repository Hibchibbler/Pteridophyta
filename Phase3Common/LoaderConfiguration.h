#ifndef LoaderConfiguration_h_
#define LoaderConfiguration_h_

#include "LoaderXML.h"

//#define DBG

namespace bali{

/*
//<configuration>
//    <client>
//        <properties>
//            <property name="foo" value="bar"/>
//            <property name="baz" value="biz"/>
//        </properties>
//        <window name="Phase 3" mode="windowed" width="800" height="800" />
//        <maps>
//            <map name="map1.tmx"/>
//        </maps>
//    </client>
//    <physics>
//        <properties>
//            <property name="bar" value="foo"/>
//        </properties>
//    </physics>
//    <networking>
//        <properties>
//            <property name="bar" value="foo"/>
//        </properties>
//    </networking>
//</configuration>
*/

class Configuration;

class LoaderConfiguration: public LoaderXML{
    public:
        LoaderConfiguration();
        ~LoaderConfiguration();
        static bool load(const char* fn, Configuration* c);
        static void save();
    private:
        static void end_element(void *data, const char *el);
        static void start_element(void *data, const char *element, const char **attribute);

    };


}//end namespace bali
#endif // ConfigurationLoader_h_
