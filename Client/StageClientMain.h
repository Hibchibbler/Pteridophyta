#ifndef StageClientMain_h_
#define StageClientMain_h_

#include "GameStage.h"


namespace bali
{
    class StageClientMain : public GameStage
    {
    public:
        StageClientMain(Game & game, uint32_t uid);
        ~StageClientMain(){}

        uint32_t initialize();
        uint32_t doRemoteEvent(CommEvent & event);
        uint32_t doWindowEvents(sf::Event & wevent);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();
    private:
        uint32_t initializeLayer(uint32_t layer);
        uint32_t addStraightQuad(sf::VertexArray & v, sf::FloatRect c, sf::IntRect t);

        sf::View mainView;
        sf::Clock localInputClock;
        uint32_t mouseInView =true;
    };
}//end namespace bali
#endif // StageClientMain_h_
