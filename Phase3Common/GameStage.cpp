#include "GameStage.h"



namespace bali{

GameStage::GameStage(Game & game, sf::Uint32 uid)
    : g(game) //reference to owner being set.
{
    done = 0;
    id = uid;
    init = 0;
}
GameStage::~GameStage()
{

}

void GameStage::setId(sf::Uint32 a)
{
    id = a;
}
sf::Uint32 GameStage::getId()
{
    return id;
}
 sf::Uint32 GameStage::isDone()
 {
     return done;
 }
 sf::Uint32 GameStage::isError()
 {
     return err;
 }

 sf::Uint32 GameStage::isInit()
 {
     return init;
 }

Game & GameStage::getOwner()
{
    return g;
}


}//end namespace bali
