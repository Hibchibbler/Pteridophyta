#ifndef Configuration_h_
#define Configuration_h_

#include <string>
#include <vector>

namespace bali{



class CfgProperty{
public:
    std::string name;
    std::string value;
};

class Window{
public:
    std::string name;
    std::string mode;
    std::string width;
    std::string height;
};

class CfgMap{
public:
    std::string name;
};

class Physics{
public:
    std::vector<CfgProperty> properties;
};

class Networking{
public:
    std::vector<CfgProperty> properties;
};

class Client{
public:
    std::vector<CfgProperty> properties;
    std::vector<CfgMap> maps;
    Window window;
};

class Configuration{
public:
    enum LoadState{
        CLIENT,
        PHYSICS,
        NETWORKING
    };
    int configLoadState;

    Client client;
    Physics physics;
    Networking networking;

};



}//end namespace bali
#endif


