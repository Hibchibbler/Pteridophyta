#include "Stage.h"

#include "Command.h"

namespace bali{


Stage::Stage(Game* game, uint32_t uid)
    : g(game) //reference to owner being set.
{
    done = 0;
    id = uid;
    init = 0;
    err = 0;
}
Stage::~Stage()
{

}

void Stage::setId(uint32_t a)
{
    id = a;
}
uint32_t Stage::getId()
{
    return id;
}
 uint32_t Stage::isDone()
 {
     return done;
 }
 uint32_t Stage::isError()
 {
     return err;
 }

 uint32_t Stage::isInit()
 {
     return init;
 }

Game* Stage::getOwner()
{
    return g;
}

void Stage::submitToComponents(std::shared_ptr<Command> cmd)
{
    auto& aSubscriberList = subscribers[cmd->getFunction()];
    for (auto& commandable: aSubscriberList)
    {
        commandable->submitCommand(cmd);
    }

}


uint32_t Stage::subscribe(uint32_t function, Commandable* c)
{
    subscribers[function].push_back(c);
    return 0;
}

}//end namespace bali
