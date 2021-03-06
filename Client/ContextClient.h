#ifndef ContextClient_h_
#define ContextClient_h_

#include "Context.h"

namespace bali{

    class ContextClient : public Context{
    public:
        std::string mapName;

        //Resolution picks
        uint32_t screenWidth;
        uint32_t screenHeight;

        sf::RenderWindow window;

        sfg::SFGUI sfGui;

        uint32_t processCommands(void* arg)
        {
            return 0;
        }
    };

}//end namespace bali
#endif

