#ifndef Game_h_
#define Game_h_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <vector>
//#include <box2d/box2d.h>//notyet
#include "ManagerPlayer.h"
#include "Commandable.h"
#include "CommandGame.h"
namespace bali{


    class Stage;

    //Game is a list of Stage's.
    //You can think of Game as a Flip book,
    //and a Stage as a page in the Flip book.
    //Game is meant to be derived. It supplies the basic infrastructure
    //to transition GameStages.
class Game : public Commandable
{
    public:
        Game();
        virtual ~Game();

        virtual uint32_t initialize();
        virtual uint32_t doEventProcessing();
        virtual uint32_t doGameProcessing();
        virtual uint32_t cleanup();

    protected:
        std::shared_ptr<Stage> getCurrentStage();
        void add(std::shared_ptr<Stage> gs);
        void clear();
        void reset();
        bool nextStage();

    private:
        uint32_t getCurrentStageIndex(){return curStageIndex;}
        uint32_t curStageIndex;
        std::vector<std::shared_ptr<Stage> > gameStages;

    };
};


#endif


