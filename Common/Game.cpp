#include "Game.h"
#include "GameStage.h"

namespace bali{

Game::Game(){
    curStageIndex = 0;
    context = NULL;
}

Game::~Game()
{

}


uint32_t Game::doEventProcessing()
{
    return 0;
}

uint32_t Game::doGameProcessing(){

    //Initialize gameStage if it has not already been initialized.
    if (!getCurrentStage()->isInit())
    {
        std::cout << "Game::doGameProcessing(): GameStage (" << getCurrentStageIndex() << ") initialized" << std::endl;
        getCurrentStage()->initialize();
    }

    //Do flows if not done
    const uint32_t NOERROR = 0;
    if (!getCurrentStage()->isDone() && getCurrentStage()->isError() == NOERROR)
    {
        getCurrentStage()->doUpdate();
        getCurrentStage()->doDraw();

    }else
    {//Stage Finished
        uint32_t e = getCurrentStage()->isError();
        if (e == 0)
        {
            //No Error. Assume Done. Goto next stage
            //But, cleanup first
            std::cout << "Game::doGameProcessing(): GameStage (" << getCurrentStageIndex() << ") finished" << std::endl;
            getCurrentStage()->cleanup();
            nextStage();
        }else{
            //Error reported from current Stage
            std::cout << "Game::doGameProcessing(): GameStage (" << getCurrentStageIndex() << ") error" << std::endl;
            getCurrentStage()->cleanup();
            return e;
        }
    }
    return 0;
}
uint32_t Game::initialize()
{

    return 0;
}

uint32_t Game::cleanup()
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
