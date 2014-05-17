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

        ReturnVal initialize();
        ReturnVal doRemoteEvent(CommEvent & event);
        ReturnVal doWindowEvent(sf::Event & event);
        ReturnVal doLocalInputs();
        ReturnVal doUpdate();
        ReturnVal doDraw();
        ReturnVal cleanup();
        uint32_t processCommands(void* arg){};
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
