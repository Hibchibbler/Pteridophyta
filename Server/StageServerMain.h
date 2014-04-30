#ifndef StageServerMain_h_
#define StageServerMain_h_

#include "Stage.h"

namespace bali
{
    class StageServerMain : public Stage
    {
    public:
        StageServerMain(Game* game, uint32_t uid);
        ~StageServerMain();

        uint32_t initialize();
        uint32_t doRemoteEvent(CommEvent & event);
        uint32_t doWindowEvent(sf::Event & event);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();

        //Commandable obligations
        uint32_t processCommands(void* arg);
    private:
    };
}//end namespace bali

#endif
