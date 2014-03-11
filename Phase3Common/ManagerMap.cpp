#include "ManagerMap.h"
#include "LoaderMap.h"
#include "ManagerConfiguration.h"

#include <iostream>
namespace bali{


ManagerMap::ManagerMap(){

}

ManagerMap::~ManagerMap(){

}

bool ManagerMap::initialize(ManagerConfiguration& cm){

    for (auto i = 0; i < cm.configuration.client.maps.size();i++){
        std::cout << "Loading Map " << cm.configuration.client.maps[i].name.c_str() << std::endl;
        std::unique_ptr<Map> aMap(new Map());
        LoaderMap::load(cm.configuration.client.maps[i].name.c_str(), aMap.get());
        maps.push_back(std::move(aMap));
    }
    return true;
}

bool ManagerMap::update(){

    return true;
}

bool ManagerMap::cleanup(){
    maps.clear();
    return true;
}



}//end namespace bali
