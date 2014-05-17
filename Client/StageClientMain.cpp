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

ReturnVal StageClientMain::initialize()
{
    Context& ctx = game->ctx;
    const uint32_t MAX_LAYERS=50;
    layers.reserve(MAX_LAYERS);

    std::cout << ctx.mp.player.name << ", "
              << ctx.mp.player.pass << ", "
              << ctx.mp.player.server_port << ", "
              << ctx.mp.player.server_ip   <<  ", "
              << ctx.mp.player.team << ", "
              << ctx.mapName << std::endl;

    mainView.setSize(ctx.screenWidth, ctx.screenHeight);

    compLevelLayer.initialize();

    //Set this so Game knows we are initialized, so it won't
    // initialize us again.
    initialized();
    return ReturnVal();
}

ReturnVal StageClientMain::doRemoteEvent(CommEvent & event)
{
    return ReturnVal();
}

ReturnVal StageClientMain::doWindowEvent(sf::Event & event)
{
    Context& ctx = game->ctx;
    switch (event.type)
    {
        case sf::Event::Resized:
            //ctx is set in parent handler
            mainView.setSize(ctx.screenWidth, ctx.screenHeight);
            break;

    }

    compLevelLayer.doWindowEvent(event);
    return ReturnVal();
}

ReturnVal StageClientMain::doLocalInputs()
{
    Context& ctx = game->ctx;

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

    compLevelLayer.doLocalInputs();
    return ReturnVal();
}
ReturnVal StageClientMain::doUpdate()
{
    Context& ctx = game->ctx;
    compLevelLayer.doUpdate();
    return ReturnVal();
}



//    //Dynamic
//    std::shared_ptr<sf::VertexArray> dynamics = std::make_shared<sf::VertexArray>(sf::PrimitiveType::Quads);
//    ManagerTile::SubSprite ss = ctx.mt.getPlayer();
//    ctx.mm.map.tileSets[ss.tsi].sprite.setTextureRect(ss.irect);
//    sf::FloatRect fr(ss.irect.left, ss.irect.top, ss.irect.width, ss.irect.height);
//    addStraightQuad(dynamics ,fr, ctx.mm.map.tileSets[ss.tsi].sprite.getTextureRect());
//    ctx.window.draw(*dynamics, &ctx.mm.map.tileSets[ss.tsi].tex);


ReturnVal StageClientMain::doDraw()
{
    Context& ctx = game->ctx;

    ctx.window.clear();
    ctx.window.resetGLStates();

    ctx.window.setView(mainView);

    //Background
    compLevelLayer.setDrawLayer(0);
    compLevelLayer.doDraw();

    //Foreground
    compLevelLayer.setDrawLayer(1);
    compLevelLayer.doDraw();

    ctx.window.display();

    return ReturnVal();
}
ReturnVal StageClientMain::cleanup()
{
    Context& ctx = game->ctx;
    compLevelLayer.cleanup();
    return ReturnVal();
}

/*
On Client:
	During Initialize:
		Load TMX Map
		Array 	 Background
		Array 	 Foreground
		QuadTree Walkables
		Quadtree Gravity Zones
		Quadtree Dynamics

	During Local Inputs:
		Update List of Commands

	During Remote Event:
		Update List of Remotes

	During Update:
		For each d in Dynamics
			Retrieve Relevant Walkables
			Retrieve Relevant Gravity Zones
			Based on current Gravity, Rotate d if needed
			update position using Commands and Remotes
			collision detect with walkables, and correct if needed
			collision detect with dynamics, and apply damage if needed
*/

}//end namespace bali
