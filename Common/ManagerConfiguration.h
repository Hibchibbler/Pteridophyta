#ifndef ManagerConfiguration_h_
#define ManagerConfiguration_h_

#include "Configuration.h"

namespace bali{


class ManagerConfiguration{
public:
    bool initialize(std::string configFileName);
    bool update();
    bool cleanup();

    Configuration configuration;
};


}//end namespace bali
#endif // ManagerConfiguration_h_
