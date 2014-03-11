#include "StageClientMain.h"
#include "GameClient.h"
#include <iostream>


namespace bali{


StageClientMain::StageClientMain(Game & game, sf::Uint32 uid)
 :  GameStage(game, uid)
{

}

sf::Uint32 StageClientMain::initialize()
{
    ContextClient *ctx = ((ContextClient*)(g.gameContext));

    std::cout << "Hi from StageClientMain::initialize() =>" << std::endl;
    std::cout << ctx->name << ", "
              << ctx->pass << ", "
              << ctx->port << ", "
              << ctx->ip   <<  ", "
              << ctx->team << std::endl;
    //Set this so Game knows we are initialized, so it won't
    // initialize us again.
    initialized();
    return 0;
}

sf::Uint32 StageClientMain::doRemoteEvents(CommEvent & cevent)
{
    return 0;
}

sf::Uint32 StageClientMain::doWindowEvents(sf::Event & wevent)
{
    return 0;
}

sf::Uint32 StageClientMain::doLocalInputs()
{
//    sf::Vector2i mousePos = sf::Mouse::getPosition(g.window);
//    sf::Vector2f mousePosWorld = g.window.mapPixelToCoords(mousePos);//,arenaView);


//    //If view shifts, then next time spacebar is hit, snap to tank...
//    //hence, viewPreset=0;
//    if (mousePosWorld.x > (arenaView.getCenter().x+(g.scrWidth/4)*zoom) ){
//        arenaView.move(100.0f, 0);
//    }else if (mousePosWorld.x < (arenaView.getCenter().x-(g.scrWidth/4)*zoom) ){
//        arenaView.move(-100.0f, 0);
//    }
//
//
//    if (mousePosWorld.y > (arenaView.getCenter().y+(g.scrHeight/4)*zoom) ){
//        arenaView.move(0, 100.0f);
//    }else if (mousePosWorld.y < (arenaView.getCenter().y-(g.scrHeight/4)*zoom) ){
//        arenaView.move(0, -100.0f);
//    }
    return 0;
}
sf::Uint32 StageClientMain::doLoop()
{
    return 0;
}
sf::Uint32 StageClientMain::doDraw()
{
    GameClient *clientGame = ((GameClient*)&g);
    clientGame->window.clear();
    clientGame->window.resetGLStates();

    //addStraightQuad(floorVertices, sf::FloatRect(tile.getPosition().x,tile.getPosition().y, 128,128), s.getTextureRect());


    clientGame->window.display();

    return 0;
}
sf::Uint32 StageClientMain::cleanup()
{
    return 0;
}


//uint32_t StageClientMain::addStraightQuad(sf::VertexArray & v, sf::FloatRect c, sf::IntRect t)
//{
//    v.append(sf::Vertex(sf::Vector2f(c.left, c.top),
//                        sf::Vector2f(t.left, t.top)
//                       ));
//
//    v.append(sf::Vertex(sf::Vector2f(c.left+c.width, c.top),
//                        sf::Vector2f(t.left+t.width, t.top)
//                       ));
//
//    v.append(sf::Vertex(sf::Vector2f(c.left+c.width, c.top+c.height),
//                        sf::Vector2f(t.left+t.width, t.top+t.height)
//                       ));
//
//    v.append(sf::Vertex(sf::Vector2f(c.left, c.top+c.height),
//                        sf::Vector2f(t.left, t.top+t.height)
//                       ));
//
//    return 0;
//}


}//end namespace bali
