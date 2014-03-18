#include "LoaderConfiguration.h"
#include "Configuration.h"

#include <vector>
#include <string>
#include <iostream>

namespace bali{




LoaderConfiguration::LoaderConfiguration()
{

}

LoaderConfiguration::~LoaderConfiguration()
{

}


bool LoaderConfiguration::load(const char* fn, Configuration *c){
    LoaderXML::load(fn, c, LoaderConfiguration::start_element, LoaderConfiguration::end_element);
    return true;
}


void LoaderConfiguration::save()
{

}

void LoaderConfiguration::end_element(void *data, const char *el)
{
#ifdef DBG
    std::cout << "</"<<el << ">" << std::endl;
#endif
}

void LoaderConfiguration::start_element(void *data, const char *element, const char **attribute)
{
#ifdef DBG
        std::cout << "<" << element << ">"<< std::endl;
        for (size_t i = 0; attribute[i]; i += 2){
            std::cout << "\t" << attribute[i]<< "=" << attribute[i+1]<< std::endl;
        }
#endif



    //LoaderConfiguration *cl = (LoaderConfiguration*)data;
    Configuration* configuration = (Configuration*)data;

    std::string elementName = element;

    if (elementName == "client"){
        configuration->configLoadState = Configuration::CLIENT;
    }
    else
    if (elementName == "server"){
        configuration->configLoadState = Configuration::CLIENT;
    }
    else
    if (elementName == "global"){
        configuration->configLoadState = Configuration::CLIENT;
    }

    if (elementName == "window" && configuration->configLoadState == Configuration::CLIENT){
        for (size_t i = 0; attribute[i]; i += 2){
            ASSIGNIFMATCHES("name", configuration->client.window.name);
            ASSIGNIFMATCHES("mode", configuration->client.window.mode);
            ASSIGNIFMATCHES("width", configuration->client.window.width);
            ASSIGNIFMATCHES("height", configuration->client.window.height);
        }
    }

    if (elementName == "map" && configuration->configLoadState == Configuration::GLOBAL){
        for (size_t i = 0; attribute[i]; i += 2){
            configuration->global.maps.push_back(Configuration::Map());
            ASSIGNIFMATCHES("name", configuration->global.maps.back().name);
        }
    }


    if (elementName == "property"){

        Configuration::Property* property = NULL;
        if (configuration->configLoadState == Configuration::CLIENT)
        {
            configuration->client.properties.push_back(Configuration::Property());
            property = &configuration->client.properties.back();
        }
        else
        if (configuration->configLoadState == Configuration::SERVER)
        {
            configuration->server.properties.push_back(Configuration::Property());
            property = &configuration->server.properties.back();
        }
        else
        if (configuration->configLoadState == Configuration::GLOBAL)
        {
            configuration->global.properties.push_back(Configuration::Property());
            property = &configuration->global.properties.back();
        }


        for (size_t i = 0; attribute[i]; i += 2){
            ASSIGNIFMATCHES("name", property->name);
            ASSIGNIFMATCHES("value", property->value);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }

}


}//end namespace bali
