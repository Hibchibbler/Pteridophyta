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
 :  Stage(game, uid)
{
}

uint32_t StageClientMain::initialize()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    const uint32_t MAX_LAYERS=50;
    layers.reserve(MAX_LAYERS);

    std::cout << cc.mp.player.name << ", "
              << cc.mp.player.pass << ", "
              << cc.mp.player.server_port << ", "
              << cc.mp.player.server_ip   <<  ", "
              << cc.mp.player.team << ", "
              << cc.mapName << std::endl;

    mainView.setSize(cc.screenWidth, cc.screenHeight);

    compLevelLayer.initialize(cc);

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
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    switch (event.type)
    {
        case sf::Event::Resized:
            //cc is set in parent handler
            mainView.setSize(cc.screenWidth, cc.screenHeight);
            break;

    }

    compLevelLayer.doWindowEvent(cc,event);
    return 0;
}

uint32_t StageClientMain::doLocalInputs()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    sf::Vector2i mousePos = sf::Mouse::getPosition(cc.window);
    sf::Vector2f mousePosWorld = cc.window.mapPixelToCoords(mousePos);//,mainView);

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

    compLevelLayer.doLocalInputs(cc);
    return 0;
}
uint32_t StageClientMain::doUpdate()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    compLevelLayer.doUpdate(cc);
    return 0;
}



//    //Dynamic
//    std::shared_ptr<sf::VertexArray> dynamics = std::make_shared<sf::VertexArray>(sf::PrimitiveType::Quads);
//    ManagerTile::SubSprite ss = cc.mt.getPlayer();
//    cc.mm.map.tileSets[ss.tsi].sprite.setTextureRect(ss.irect);
//    sf::FloatRect fr(ss.irect.left, ss.irect.top, ss.irect.width, ss.irect.height);
//    addStraightQuad(dynamics ,fr, cc.mm.map.tileSets[ss.tsi].sprite.getTextureRect());
//    cc.window.draw(*dynamics, &cc.mm.map.tileSets[ss.tsi].tex);


uint32_t StageClientMain::doDraw()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    cc.window.clear();
    cc.window.resetGLStates();

    cc.window.setView(mainView);

    //Background
    compLevelLayer.setDrawLayer(0);
    compLevelLayer.doDraw(cc);

    //Foreground
    compLevelLayer.setDrawLayer(1);
    compLevelLayer.doDraw(cc);

    cc.window.display();

    return 0;
}
uint32_t StageClientMain::cleanup()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    compLevelLayer.cleanup(cc);
    return 0;
}



}//end namespace bali
