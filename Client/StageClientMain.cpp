#include "StageClientMain.h"
#include "Util.h"
#include "GameClient.h"
#include "ManagerTile.h"
#include "CompLevelLayer.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <memory>

namespace bali{


StageClientMain::StageClientMain(Game* game, uint32_t uid)
 :  GameStage(game, uid)
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


    //Load all layers. We assume layers contain static content.
    uint32_t numLayers = cc.mm.map.layers.size();
    for (int i = 0;i < numLayers;i++)
    {
        layers.push_back(sf::VertexArray(sf::PrimitiveType::Quads));
        cc.mm.initializeLayer(i, layers.back());

    }

//    std::shared_ptr<Component> comp;
//    comp = std::make_shared<CompBackgnd>();
//    addComponent(comp);

//    comp = std::make_shared<CompDynObjects>();
//    addComponent(comp);
//
//    comp = std::make_shared<CompForegnd>();
//    addComponent(comp);
//
//    comp = std::make_shared<CompHUD>();
//    addComponent(comp);
//
//    comp = std::make_shared<CompMiniMap>();
//    addComponent(comp);



    //Set this so Game knows we are initialized, so it won't
    // initialize us again.
    initialized();
    return 0;
}

uint32_t StageClientMain::doRemoteEvent(CommEvent & event)
{
    return 0;
}

uint32_t StageClientMain::doWindowEvents(sf::Event & wevent)
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);
    switch (wevent.type)
    {
        case sf::Event::Resized:
            //cc is set in parent handler
            mainView.setSize(cc.screenWidth, cc.screenHeight);
            break;

    }
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
    return 0;
}
uint32_t StageClientMain::doUpdate()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    for (auto& c: components)
    {
        c->doUpdate();
    }

    return 0;
}

uint32_t StageClientMain::doDraw()
{
    ContextClient& cc = GET_CLIENT_CONTEXT(g);

    cc.window.clear();
    cc.window.resetGLStates();


    for (auto& c: components)
    {
        c->doDraw();
    }
    ////
    cc.window.setView(mainView);

    //Let's assume layer0 in tmx is background
    //we then draw dynamic stuff, like players, monsters, and explosions
    //and then layer1 in tmx is foreground


    //Background
    //sf::VertexArray& va;
    uint32_t gid, tsi;
    gid = cc.mm.getFirstNonZeroGidInLayer(0);
    tsi = cc.mm.getTileSetIndexByGid(gid);
    //va  = layers[0];
    cc.window.draw(layers[0], &cc.mm.map.tileSets[tsi].tex);

//    //Dynamic
//    std::shared_ptr<sf::VertexArray> dynamics = std::make_shared<sf::VertexArray>(sf::PrimitiveType::Quads);
//
//    ManagerTile::SubSprite ss = cc.mt.getPlayer();
//    cc.mm.map.tileSets[ss.tsi].sprite.setTextureRect(ss.irect);
//
//    sf::FloatRect fr(ss.irect.left, ss.irect.top, ss.irect.width, ss.irect.height);
//    addStraightQuad(dynamics ,fr, cc.mm.map.tileSets[ss.tsi].sprite.getTextureRect());
//    cc.window.draw(*dynamics, &cc.mm.map.tileSets[ss.tsi].tex);
//
//    //Foreground
//    gid = cc.mm.getFirstNonZeroGidInLayer(1);
//    tsi = cc.mm.getTileSetIndexByGid(gid);
//    va  = layers[1];
//    cc.window.draw(*va, &cc.mm.map.tileSets[tsi].tex);


    cc.window.display();

    return 0;
}
uint32_t StageClientMain::cleanup()
{
    return 0;
}



}//end namespace bali
