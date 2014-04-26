#ifndef StageClientMain_h_
#define StageClientMain_h_

#include "Stage.h"
#include "CompDrawLayers.h"

namespace bali
{
    class StageClientMain : public Stage
    {
    public:
        StageClientMain(Game* game, uint32_t uid);
        ~StageClientMain(){}

        uint32_t initialize();
        uint32_t doRemoteEvent(CommEvent & event);
        uint32_t doWindowEvent(sf::Event & event);
        uint32_t doLocalInputs();
        uint32_t doUpdate();
        uint32_t doDraw();
        uint32_t cleanup();
        uint32_t processCommands(){};
    private:
        CompDrawLayers compLevelLayer;

        uint32_t addStraightQuad(std::shared_ptr<sf::VertexArray> v, sf::FloatRect c, sf::IntRect t);

        sf::View mainView;
        sf::Clock localInputClock;
        uint32_t mouseInView =true;
        std::vector<sf::VertexArray> layers;
    };
}//end namespace bali
#endif // StageClientMain_h_
