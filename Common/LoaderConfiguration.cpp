#include "LoaderConfiguration.h"
#include "ManagerConfiguration.h"

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


bool LoaderConfiguration::load(const char* fn, ManagerConfiguration* c){
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
    ManagerConfiguration* configuration = (ManagerConfiguration*)data;

    std::string elementName = element;

    if (elementName == "client"){
        configuration->configLoadState = ManagerConfiguration::CLIENT;
    }
    else
    if (elementName == "server"){
        configuration->configLoadState = ManagerConfiguration::SERVER;
    }
    else
    if (elementName == "global"){
        configuration->configLoadState = ManagerConfiguration::GLOBAL;
    }

    if (elementName == "window" && configuration->configLoadState == ManagerConfiguration::CLIENT){
        for (size_t i = 0; attribute[i]; i += 2){
            ASSIGNIFMATCHESSTR("name", configuration->client.window.name);
            ASSIGNIFMATCHESSTR("mode", configuration->client.window.mode);
            ASSIGNIFMATCHESINT("width", configuration->client.window.width);
            ASSIGNIFMATCHESINT("height", configuration->client.window.height);
        }
    }

    if (elementName == "map" && configuration->configLoadState == ManagerConfiguration::GLOBAL){
        configuration->global.maps.push_back(ManagerConfiguration::Map());
        for (size_t i = 0; attribute[i]; i += 2){
            ASSIGNIFMATCHESSTR("id", configuration->global.maps.back().id);
            ASSIGNIFMATCHESSTR("filepath", configuration->global.maps.back().filePath);
        }
    }


    if (elementName == "property"){

        std::map<std::string, std::string>* properties = NULL;
        if (configuration->configLoadState == ManagerConfiguration::CLIENT)
        {
            //configuration->client.properties.push_back(ManagerConfiguration::Property());
            properties = &configuration->client.properties;//.back();
        }
        else
        if (configuration->configLoadState == ManagerConfiguration::SERVER)
        {
            //configuration->server.properties.push_back(ManagerConfiguration::Property());
            properties = &configuration->server.properties;//.back();
        }
        else
        if (configuration->configLoadState == ManagerConfiguration::GLOBAL)
        {
            //configuration->global.properties.push_back(ManagerConfiguration::Property());
            properties = &configuration->global.properties;//.back();
        }

        std::string n,v;
        for (size_t i = 0; attribute[i]; i += 2){
            ASSIGNIFMATCHESSTR("name", n);
            ASSIGNIFMATCHESSTR("value", v);
            if (n != "")
                (*properties)[n]=v;
            n= v= "";
            std::cout << "Unexpected attribute " << attribute[i] << "=" << attribute[i+1] << " in " << std::string(element) << std::endl;
        }
    }

}


}//end namespace bali
