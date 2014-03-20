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

    for (auto i = 0; i < cm.configuration.global.maps.size();i++){
        std::cout << "Loading Map " << cm.configuration.global.maps[i].filePath.c_str() << std::endl;
        std::unique_ptr<Map> aMap(new Map());
        LoaderMap::load(cm.configuration.global.maps[i].filePath.c_str(), aMap.get());
        maps[cm.configuration.global.maps[i].id] = std::move(aMap);
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
