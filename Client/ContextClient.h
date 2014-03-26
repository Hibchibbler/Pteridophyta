#ifndef ContextClient_h_
#define ContextClient_h_

namespace bali{

    class ContextClient{
    public:
        std::string name;
        std::string pass;
        std::string port;
        std::string ip;
        int team;
        std::string layerName;

        //Resolution picks
        uint32_t screenWidth;
        uint32_t screenHeight;
    };

}//end namespace bali
#endif

