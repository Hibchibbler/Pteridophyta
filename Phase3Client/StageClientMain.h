#ifndef StageClientMain_h_
#define StageClientMain_h_

#include "GameStage.h"
namespace bali
{
    class StageClientMain : public GameStage
    {
    public:
        StageClientMain(Game & game, sf::Uint32 uid);
        ~StageClientMain(){}

        sf::Uint32 initialize();
        sf::Uint32 doRemoteEvents(CommEvent & cevent);
        sf::Uint32 doWindowEvents(sf::Event & wevent);
        sf::Uint32 doLocalInputs();
        sf::Uint32 doLoop();
        sf::Uint32 doDraw();
        sf::Uint32 cleanup();
    private:

    };
}//end namespace bali
#endif // StageClientMain_h_
