#ifndef StageServerMain_h_
#define StageServerMain_h_

namespace bali
{
    class StageServerMain : public GameStage
    {
    public:
        StageServerMain(Game & game, sf::Uint32 uid);
        ~StageServerMain();

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

#endif
