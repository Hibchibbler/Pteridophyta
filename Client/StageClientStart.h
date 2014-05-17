#ifndef StageClientStart_h_
#define StageClientStart_h_

#include "Stage.h"
#include <SFGUI/sfgui.hpp>


namespace bali
{
    class StageClientStart : public Stage
    {
    public:
        StageClientStart(Game* game, uint32_t uid);
        ~StageClientStart();

        ReturnVal initialize();
        ReturnVal doRemoteEvent(CommEvent & event);
        ReturnVal doWindowEvent(sf::Event & event);
        ReturnVal doLocalInputs();
        ReturnVal doUpdate();
        ReturnVal doDraw();
        ReturnVal cleanup();

        //Commandable obligations
        uint32_t processCommands(void* arg);
    private:
//        std::vector<std::shared_ptr<Component>> components;

    };
}

#endif // StageClientStart_h_

