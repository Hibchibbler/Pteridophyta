#include "Game.h"
#include "Stage.h"

namespace bali{

Game::Game(){
    curStageIndex = 0;
}

Game::~Game()
{

}


uint32_t Game::doEventProcessing()
{
    //Initialize gameStage if it has not already been initialized.
    if (!getCurrentStage()->isInit())
    {
        std::cout << "Game::doEventProcessing(): Stage (" << getCurrentStageIndex() << ") initialized" << std::endl;
        getCurrentStage()->initialize();
    }
    return 0;
}

uint32_t Game::doGameProcessing(){

    //N.B. - Stage was initialized in doEventProcessing
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
            std::cout << "Game::doGameProcessing(): Stage (" << getCurrentStageIndex() << ") finished" << std::endl;
            getCurrentStage()->cleanup();
            nextStage();
        }else{
            //Error reported from current Stage
            std::cout << "Game::doGameProcessing(): Stage (" << getCurrentStageIndex() << ") error" << std::endl;
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

void Game::add(std::shared_ptr<Stage> gs){
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

std::shared_ptr<Stage> Game::getCurrentStage()
{
    return gameStages[curStageIndex];
}

}
