#ifndef Game_h_
#define Game_h_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include "Stage.h"
#include <vector>
//#include <box2d/box2d.h>//notyet
#include "ManagerPlayer.h"
#include "Commandable.h"
#include "CommandGame.h"
#include "Context.h"
namespace bali{


    //class Stage;

    //Game is a list of Stage's.
    //You can think of Game as a Flip book,
    //and a Stage as a page in the Flip book.
    //Game is meant to be derived. It supplies the basic infrastructure
    //to transition GameStages.
class Game : public Commandable
{
    public:
        struct ReturnVal{
            enum class Code{
                SUCCESS,
                ERROR
            };
            Code code;
        };
        Game();
        virtual ~Game();

        virtual uint32_t initialize();
        virtual uint32_t doEventProcessing();
        virtual uint32_t doGameProcessing();
        virtual uint32_t cleanup();

        Context ctx;
    protected:
        Stage::Ptr getCurrentStage();
        void add(Stage::Ptr gs);
        void clear();
        void reset();
        bool nextStage();

    private:
        uint32_t getCurrentStageIndex(){return curStageIndex;}
        uint32_t curStageIndex;
        std::vector<Stage::Ptr> gameStages;

    };
};


#endif


