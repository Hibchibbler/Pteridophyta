#include "ManagerConfiguration.h"
#include "LoaderConfiguration.h"


namespace bali{


bool ManagerConfiguration::initialize(std::string configFileName){
    LoaderConfiguration::load(configFileName.c_str(), &configuration);
    return true;
}
bool ManagerConfiguration::update(){

    return true;
}
bool ManagerConfiguration::cleanup(){
    return true;
}


}//end namespace bali

