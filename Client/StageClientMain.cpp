#include "StageClientMain.h"
#include "Util.h"
#include "GameClient.h"
#include "ManagerTile.h"
#include "CompDrawLayers.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <memory>

namespace bali{


StageClientMain::StageClientMain(Game* game, uint32_t uid)
 :  Stage(game, uid), compLevelLayer(this)
{
}

uint32_t StageClientMain::initialize()
{
    Context& ctx = g->ctx;
    const uint32_t MAX_LAYERS=50;
    layers.reserve(MAX_LAYERS);

    std::cout << ctx.mp.player.name << ", "
              << ctx.mp.player.pass << ", "
              << ctx.mp.player.server_port << ", "
              << ctx.mp.player.server_ip   <<  ", "
              << ctx.mp.player.team << ", "
              << ctx.mapName << std::endl;

    mainView.setSize(ctx.screenWidth, ctx.screenHeight);

    compLevelLayer.initialize(ctx);

    //Set this so Game knows we are initialized, so it won't
    // initialize us again.
    initialized();
    return 0;
}

uint32_t StageClientMain::doRemoteEvent(CommEvent & event)
{
    return 0;
}

uint32_t StageClientMain::doWindowEvent(sf::Event & event)
{
    Context& ctx = g->ctx;
    switch (event.type)
    {
        case sf::Event::Resized:
            //ctx is set in parent handler
            mainView.setSize(ctx.screenWidth, ctx.screenHeight);
            break;

    }

    compLevelLayer.doWindowEvent(ctx,event);
    return 0;
}

uint32_t StageClientMain::doLocalInputs()
{
    Context& ctx = g->ctx;

    sf::Vector2i mousePos = sf::Mouse::getPosition(ctx.window);
    sf::Vector2f mousePosWorld = ctx.window.mapPixelToCoords(mousePos);//,mainView);

    const float MAIN_VIEW_MOVE_AMOUNT = 25.0f;
    if (localInputClock.getElapsedTime().asSeconds() > 0.1)
    {
//        if (mousePosWorld.x > (mainView.getCenter().x+(ctx->screenWidth/4)*1) ){
//            mainView.move(MAIN_VIEW_MOVE_AMOUNT, 0);
//        }else if (mousePosWorld.x < (mainView.getCenter().x-(ctx->screenWidth/4)*1) ){
//            mainView.move(-MAIN_VIEW_MOVE_AMOUNT, 0);
//        }
//        if (mousePosWorld.y > (mainView.getCenter().y+(ctx->screenHeight/4)*1) ){
//            mainView.move(0, MAIN_VIEW_MOVE_AMOUNT);
//        }else if (mousePosWorld.y < (mainView.getCenter().y-(ctx->screenHeight/4)*1) ){
//            mainView.move(0, -MAIN_VIEW_MOVE_AMOUNT);
//        }
        localInputClock.restart();
    }

    compLevelLayer.doLocalInputs(ctx);
    return 0;
}
uint32_t StageClientMain::doUpdate()
{
    Context& ctx = g->ctx;
    compLevelLayer.doUpdate(ctx);
    return 0;
}



//    //Dynamic
//    std::shared_ptr<sf::VertexArray> dynamics = std::make_shared<sf::VertexArray>(sf::PrimitiveType::Quads);
//    ManagerTile::SubSprite ss = ctx.mt.getPlayer();
//    ctx.mm.map.tileSets[ss.tsi].sprite.setTextureRect(ss.irect);
//    sf::FloatRect fr(ss.irect.left, ss.irect.top, ss.irect.width, ss.irect.height);
//    addStraightQuad(dynamics ,fr, ctx.mm.map.tileSets[ss.tsi].sprite.getTextureRect());
//    ctx.window.draw(*dynamics, &ctx.mm.map.tileSets[ss.tsi].tex);


uint32_t StageClientMain::doDraw()
{
    Context& ctx = g->ctx;

    ctx.window.clear();
    ctx.window.resetGLStates();

    ctx.window.setView(mainView);

    //Background
    compLevelLayer.setDrawLayer(0);
    compLevelLayer.doDraw(ctx);

    //Foreground
    compLevelLayer.setDrawLayer(1);
    compLevelLayer.doDraw(ctx);

    ctx.window.display();

    return 0;
}
uint32_t StageClientMain::cleanup()
{
    Context& ctx = g->ctx;
    compLevelLayer.cleanup(ctx);
    return 0;
}



}//end namespace bali
