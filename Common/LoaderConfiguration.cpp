#include "LoaderConfiguration.h"
#include "Configuration.h"

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

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
        configuration->configLoadState = Configuration::SERVER;
    }
    else
    if (elementName == "global"){
        configuration->configLoadState = Configuration::GLOBAL;
    }

    if (elementName == "window" && configuration->configLoadState == Configuration::CLIENT){
        for (size_t i = 0; attribute[i]; i += 2){
            ASSIGNIFMATCHESSTR("name", configuration->client.window.name);
            ASSIGNIFMATCHESSTR("mode", configuration->client.window.mode);
            ASSIGNIFMATCHESINT("width", configuration->client.window.width);
            ASSIGNIFMATCHESINT("height", configuration->client.window.height);
        }
    }

    if (elementName == "map" && configuration->configLoadState == Configuration::GLOBAL){
        configuration->global.maps.push_back(Configuration::Map());
        for (size_t i = 0; attribute[i]; i += 2){
            ASSIGNIFMATCHESSTR("id", configuration->global.maps.back().id);
            ASSIGNIFMATCHESSTR("filepath", configuration->global.maps.back().filePath);
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
            ASSIGNIFMATCHESSTR("name", property->name);
            ASSIGNIFMATCHESSTR("value", property->value);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }

}


}//end namespace bali
