#ifndef Configuration_h_
#define Configuration_h_

#include <string>
#include <vector>

namespace bali{

class Configuration{
public:
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
        std::vector<Property> properties;
        Window window;
    };

    struct Server{
        std::vector<Property> properties;
    };

    struct Global{
        std::vector<Map> maps;
        std::vector<Property> properties;
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


