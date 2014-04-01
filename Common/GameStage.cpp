#include "GameStage.h"



namespace bali{

GameStage::GameStage(Game* game, uint32_t uid)
    : g(game) //reference to owner being set.
{
    done = 0;
    id = uid;
    init = 0;
    err = 0;
}
GameStage::~GameStage()
{

}

void GameStage::setId(uint32_t a)
{
    id = a;
}
uint32_t GameStage::getId()
{
    return id;
}
 uint32_t GameStage::isDone()
 {
     return done;
 }
 uint32_t GameStage::isError()
 {
     return err;
 }

 uint32_t GameStage::isInit()
 {
     return init;
 }

Game* GameStage::getOwner()
{
    return g;
}


}//end namespace bali
