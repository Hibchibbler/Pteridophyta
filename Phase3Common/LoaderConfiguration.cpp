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

    if (elementName == "configuration"){
        //configState = Configuration::CONFIG;//not used
    }

    if (elementName == "client"){
        configuration->configLoadState = Configuration::CLIENT;
    }

    if (elementName == "window"){
        for (size_t i = 0; attribute[i]; i += 2){
            assignIfMatches("name", configuration->client.window.name);
            assignIfMatches("mode", configuration->client.window.mode);
            assignIfMatches("width", configuration->client.window.width);
            assignIfMatches("height", configuration->client.window.height);
        }
    }

    if (elementName == "map"){
        for (size_t i = 0; attribute[i]; i += 2){
            configuration->client.maps.push_back(CfgMap());
            assignIfMatches("name", configuration->client.maps.back().name);
        }
    }

    if (elementName == "physics"){
        configuration->configLoadState = Configuration::PHYSICS;
    }

    if (elementName == "networking"){
        configuration->configLoadState = Configuration::NETWORKING;
    }

    if (elementName == "property"){
        CfgProperty* property = NULL;
        if (configuration->configLoadState == Configuration::CLIENT){
            configuration->client.properties.push_back(CfgProperty());
            property = &configuration->client.properties.back();
        }else
        if (configuration->configLoadState == Configuration::PHYSICS){
            configuration->physics.properties.push_back(CfgProperty());
            property = &configuration->physics.properties.back();
        }else
        if (configuration->configLoadState == Configuration::NETWORKING){
            configuration->networking.properties.push_back(CfgProperty());
            property = &configuration->networking.properties.back();
        }
        for (size_t i = 0; attribute[i]; i += 2){
            assignIfMatches("name", property->name);
            assignIfMatches("value", property->value);
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }

}


}//end namespace bali
