#ifndef Game_h_
#define Game_h_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <vector>
#include <box2d/box2d.h>
#include "ManagerPlayer.h"

namespace bali{


    class GameStage;


    class GameContext{
    public:

    };
    //Game is a list of GameStage's.
    // Meant to be derived
    class Game
    {
    public:
        Game(){
            curStageIndex = 0;
            gameContext = NULL;
        }
        virtual ~Game(){

        }

        virtual sf::Uint32 initialize();
        virtual sf::Uint32 doEventProcessing();
        virtual sf::Uint32 doGameProcessing();
        virtual sf::Uint32 cleanup();

        void* getContext(){return gameContext;}
        void setContext(void* s){gameContext = s;}

        void reset();
        bool nextStage();
        std::shared_ptr<GameStage> getCurrentStage();
        void add(std::shared_ptr<GameStage> gs);
        void clear();

        void* gameContext;
    private:



        sf::Uint32 curStageIndex;
        std::vector<std::shared_ptr<GameStage> > gameStages;


    };
};


#endif


