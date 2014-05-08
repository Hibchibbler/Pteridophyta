#ifndef ManagerConfiguration_h_
#define ManagerConfiguration_h_

#include <string>
#include <vector>
#include <map>

namespace bali{

class ManagerConfiguration{
public:
    bool initialize(std::string configFileName);
    bool update();
    bool cleanup();

    struct Property{
        std::string name;
        std::string value;
    };

    struct Window{
        std::string name;
        std::string mode;
        uint32_t    width;
        uint32_t    height;
    };

    struct Map{
        std::string id;
        std::string filePath;
    };

    struct Client{
        std::map<std::string, std::string> properties;
        Window window;
    };

    struct Server{
        std::map<std::string, std::string> properties;
    };

    struct Global{
        std::vector<Map> maps;
        std::map<std::string, std::string> properties;
    };


    enum LoadState{
        CLIENT,
        SERVER,
        GLOBAL
    };
    int configLoadState;

    Client client;
    Server server;
    Global global;

};



}//end namespace bali
#endif


