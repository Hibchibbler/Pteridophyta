#include "Game.h"
#include "GameStage.h"

namespace bali{

sf::Uint32 Game::doEventProcessing()
{
    return 0;
}

sf::Uint32 Game::doGameProcessing(){

    //Initialize gameStage if it has not already been initialized.
    //This is only applicable to the very first stage.
    if (!getCurrentStage()->isInit())
        getCurrentStage()->initialize();

    //Check if current stage is done
    if (getCurrentStage()->isDone())
    {
        if (!getCurrentStage()->isError())
        {
            //Goto next stage
            nextStage();

            //initialize stage right after we transition to it.
            getCurrentStage()->initialize();
        }else{
            //Done and Error reported from current Stage
        }
    }


    getCurrentStage()->doLoop();
    getCurrentStage()->doDraw();

    return 0;
}
sf::Uint32 Game::initialize()
{

    return 0;
}

sf::Uint32 Game::cleanup()
{
    gameStages.clear();
    curStageIndex = 0;
    return 0;
}

void Game::add(std::shared_ptr<GameStage> gs){
    gameStages.push_back(gs);
}

bool Game::nextStage()
{
    if (curStageIndex < gameStages.size()){
        curStageIndex++;
        return true;
    }
    return false;
}

std::shared_ptr<GameStage> Game::getCurrentStage()
{
    return gameStages[curStageIndex];
}

}
