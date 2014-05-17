
#include "StageClientLobby.h"
#include "GameClient.h"
#include "Comm.h"
#include "Messages.h"
#include <SFGUI\SFGUI.hpp>
#include "Command.h"
#include "CompLogicLobby.h"


namespace bali{

using namespace sfg;

StageClientLobby::StageClientLobby(Game* game, uint32_t uid)
    : Stage(game, uid)
{
}

StageClientLobby::~StageClientLobby()
{
}

ReturnVal StageClientLobby::initialize()
{
    //Add Components
    components.push_back(std::make_shared<CompWindowLobby>(this));
    components.push_back(std::make_shared<CompLogicLobby>(this));



    //Initialize Component Command Subscribers
    //Creates an empty vector for each command function
    subscribers[CommandComponent::Functions::PAUSE];
    subscribers[CommandComponent::Functions::RESUME];
    subscribers[CommandComponent::Functions::SHOW];
    subscribers[CommandComponent::Functions::HIDE];
    subscribers[CommandComponent::Functions::PROCESSIDNACKMSG];
    subscribers[CommandComponent::Functions::PROCESSIDACKMSG];
    subscribers[CommandComponent::Functions::PROCESSWHOISACKMSG];

    //Initialize all components.
    //they each will subscribe to some, all, or none of the functions initialized above..
    for (auto& c : components)
    {
        c->initialize();
    }
    initialized();
    return ReturnVal();
}

ReturnVal StageClientLobby::doWindowEvent(sf::Event & event)
{
    for (auto& c : components)
    {
        c->doWindowEvent(event);
    }

    return ReturnVal();
}

ReturnVal StageClientLobby::doRemoteEvent(CommEvent & event)
{
    for (auto& c : components)
    {
        c->doRemoteEvent(event);
    }

    return ReturnVal();
}
uint32_t StageClientLobby::processCommands(void* arg)
{
    Context& ctx = game->ctx;
    for (auto& c : commands)
    {
        switch (c->getFunction())
        {
            case CommandStage::Functions::STAGEFINISH:
                std::cout << "Processing STAGEFINISH" << std::endl;
                finished(0);
                break;
            case CommandStage::Functions::SENDWHOIS:
                Messages::sendWhoIs(ctx.net, ctx.mp.player);
                break;
            case CommandStage::Functions::SENDID:
                Messages::sendId(ctx.net, ctx.mp.player);
                break;
            case CommandStage::Functions::SENDREADY:
                Messages::sendReady(ctx.net, ctx.mp.player);

                //
                //The player is ready when we recieve Ready from client.
                //And player is identified.
                //
                if (ctx.mp.player.isIdentified())
                    ctx.mp.player.setReady();
                else
                    std::cout << "Ready received, but not identified yet." << std::endl;

                break;
        }
    }

    commands.clear();
    return 0;
}

ReturnVal StageClientLobby::doUpdate()
{
    //Process Queued Stage Commands
    processCommands(nullptr);

    //Send WhoIs every 1 seconds to update lobby lists
    if (sendWhoIsClk.getElapsedTime().asSeconds() > 1)
    {
        submitCommand(std::make_shared<CommandStage>(CommandStage::Functions::SENDWHOIS, nullptr));
        sendWhoIsClk.restart();
    }

    for (auto& c : components)
    {
        c->doUpdate();
    }

    return ReturnVal();
}
ReturnVal StageClientLobby::doLocalInputs()
{
    for (auto& c : components)
    {
        c->doLocalInputs();
    }

    return ReturnVal();
}


ReturnVal StageClientLobby::doDraw()
{
    Context& ctx = game->ctx;
    ctx.window.clear();

    for (auto& c : components)
    {
        c->doDraw();
    }

    ctx.window.display();
    return ReturnVal();
}

ReturnVal StageClientLobby::cleanup()
{
    for (auto& c : components)
    {
        c->cleanup();
    }

    return ReturnVal();
}

}//end namespace bali
