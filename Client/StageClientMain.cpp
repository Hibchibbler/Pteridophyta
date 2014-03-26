#include "StageClientMain.h"
#include "GameClient.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdlib.h>

namespace bali{


StageClientMain::StageClientMain(Game & game, uint32_t uid)
 :  GameStage(game, uid)
{

}

uint32_t StageClientMain::initialize()
{
    ContextClient *ctx = ((ContextClient*)(g.getContext()));

    std::cout << ctx->name << ", "
              << ctx->pass << ", "
              << ctx->port << ", "
              << ctx->ip   <<  ", "
              << ctx->team << ", "
              << ctx->layerName << std::endl;

    mainView.setSize(ctx->screenWidth, ctx->screenHeight);

    const uint32_t LAYER_0 = 0;
    initializeLayer(LAYER_0);



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
    ContextClient *ctx = ((ContextClient*)(g.getContext()));
    switch (wevent.type)
    {
        case sf::Event::Resized:
            //ctx is set in parent handler
            mainView.setSize(ctx->screenWidth, ctx->screenHeight);
            break;

    }
    return 0;
}

uint32_t StageClientMain::doLocalInputs()
{
    GameClient* gc = (GameClient*)&g;
    ContextClient *ctx = ((ContextClient*)(g.getContext()));
    sf::Vector2i mousePos = sf::Mouse::getPosition(gc->window);
    sf::Vector2f mousePosWorld = gc->window.mapPixelToCoords(mousePos);//,mainView);


    if (localInputClock.getElapsedTime().asSeconds() > 0.1)
    {
        sf::Vector2i mousePosB = sf::Mouse::getPosition();

        sf::IntRect screenRect((mainView.getCenter().x - mainView.getSize().x/2),(mainView.getCenter().y - mainView.getSize().y/2),mainView.getSize().x,mainView.getSize().y);

        if (screenRect.contains(mousePosB.x, mousePosB.y))
        {
            mouseInView=false;
        }else
        {
            mouseInView=true;
        }
        if (mouseInView)
        {
            if (mousePosWorld.x > (mainView.getCenter().x+(ctx->screenWidth/4)*1) ){
                mainView.move(100.0f, 0);
            }else if (mousePosWorld.x < (mainView.getCenter().x-(ctx->screenWidth/4)*1) ){
                mainView.move(-100.0f, 0);
            }
            if (mousePosWorld.y > (mainView.getCenter().y+(ctx->screenHeight/4)*1) ){
                mainView.move(0, 100.0f);
            }else if (mousePosWorld.y < (mainView.getCenter().y-(ctx->screenHeight/4)*1) ){
                mainView.move(0, -100.0f);
            }
        }
        localInputClock.restart();
    }
    return 0;
}
uint32_t StageClientMain::doUpdate()
{
    GameClient *cg = ((GameClient*)&g);
    ContextClient *ctx = ((ContextClient*)(g.getContext()));

    return 0;
}



//this algorithm assumes '0' as first index
//
bool indexToPos(int index, int & r, int & c, int tiles_wide, int tile_width, int tile_height)
{
    r = (index % tiles_wide) * tile_width;
    c = (index / tiles_wide) * tile_height;
    return true;
}
void posToIndex(sf::Vector2f pos, int & index, int tiles_wide, int tile_width, int tile_height)
{
    int w,h;
    w = tile_width;
    h = tile_height;
    int gridCoordX = (((int)pos.x / w) * w);
    int gridCoordY = (((int)pos.y / h) * h);
    int mapCoordX = gridCoordX / w;
    int mapCoordY = gridCoordY / h;
    index = mapCoordX + (mapCoordY*tiles_wide);
}


uint32_t getTileSetIndexByGid(uint32_t gid, const std::shared_ptr<Map> & map)
{
    //Find the tileset to which this gid refers.
    //iterate through each tileset and check if gid is between the firstgid and lastgid. if so
    //then set tileset as current.
    uint32_t maxTileSetGid=0;

    for (int currentTileSet = 0; currentTileSet < map->tileSets.size(); currentTileSet++)
    {
        uint32_t maxTileSetGidW = map->tileSets[currentTileSet].image.width  / map->tileSets[currentTileSet].tileWidth;
        uint32_t maxTileSetGidH = map->tileSets[currentTileSet].image.height / map->tileSets[currentTileSet].tileHeight;
        maxTileSetGid  += maxTileSetGidW*maxTileSetGidH;

        if (map->tileSets[currentTileSet].firstgid <= gid && gid <= maxTileSetGid)
        {//t is the tileSet index we want
            return currentTileSet;
        }
    }
    return -1;
}

uint32_t StageClientMain::initializeLayer(uint32_t layer)
{
    //N.B. - assuming width == height in a lot of places
    GameClient*                 gc              = ((GameClient*)&g);
    std::shared_ptr<Map>        map             = gc->mm.map;
    std::vector<Map::Tile>&     tiles           = map->layers[layer].data[0].tiles;
                                gc->layer1      = sf::VertexArray(sf::PrimitiveType::Quads);
    uint32_t                    mapWidth        = map->width;
    int                         numTileSets     = map->tileSets.size();

    for (int index = 0; index < tiles.size();index++)
    {

        //current gid
        uint32_t gid = tiles[index].gid;

        //Find the tileset to which this gid refers. - gid MUST be valid
        uint32_t currentTileSet  = getTileSetIndexByGid(gid, map);

        //Get all the things we need from this tileset.
        uint32_t firstGid        = map->tileSets[currentTileSet].firstgid;

        uint32_t tileWidth       = map->tileSets[currentTileSet].tileWidth;
        uint32_t tileHeight      = map->tileSets[currentTileSet].tileHeight;

        uint32_t imageWidth      = map->tileSets[currentTileSet].image.width;
        uint32_t imageHeight     = map->tileSets[currentTileSet].image.height;

        //This converts a global id to a local id.
        uint32_t lid             = gid - firstGid;

        //This is where we map the current gid to the upper left corner of a region in a sprite sheet.
        //Convert current gid to the upper left corner(x,y) of a sub rect that represents a particular sprite.
        int y,x;
        indexToPos(lid, y, x, imageWidth, tileWidth,tileHeight);//parameter 4 is how many tiles wide the sprite sheet is.

        //Then, Set the sub rect for the sprite
        map->tileSets[currentTileSet].sprite.setTextureRect(sf::IntRect(y,x,tileWidth,tileHeight));

        //This is where we use the implied position in an array to map to a screen position.
        //Convert index to the upper left corner(x,y) of a tile sized region on the screen.
        //Index represents the implied position of the tile in the tiles vector.
        //In a TMX file, there is <Layer><Data><Tile><Tile>...<Tile></Data></Layer>
        int r1, c1;
        float x1,y1;
        indexToPos(index, r1, c1, mapWidth, tileWidth, tileHeight);//parameter 4 is how many tiles wide the map is.
        x1 = (float)c1;
        y1 = (float)r1;

        //Add a quad the size of a tile. and specify the texture coordinates using the sub rect specified earlier.
        addStraightQuad(gc->layer1, sf::FloatRect(y1,x1, tileWidth,tileHeight), map->tileSets[currentTileSet].sprite.getTextureRect());
    }
    return 0;
}

uint32_t StageClientMain::doDraw()
{
    GameClient *gc = ((GameClient*)&g);
    //ContextClient *ctx = ((ContextClient*)(g.getContext()));

    gc->window.clear();
    gc->window.resetGLStates();

    ////
    gc->window.setView(mainView);
    gc->window.draw(gc->layer1, &gc->mm.map->tileSets[0].tex);

    gc->window.display();

    return 0;
}
uint32_t StageClientMain::cleanup()
{
    return 0;
}


uint32_t StageClientMain::addStraightQuad(sf::VertexArray & v, sf::FloatRect c, sf::IntRect t)
{
    v.append(sf::Vertex(sf::Vector2f(c.left, c.top),
                        sf::Vector2f(t.left, t.top)
                       ));

    v.append(sf::Vertex(sf::Vector2f(c.left+c.width, c.top),
                        sf::Vector2f(t.left+t.width, t.top)
                       ));

    v.append(sf::Vertex(sf::Vector2f(c.left+c.width, c.top+c.height),
                        sf::Vector2f(t.left+t.width, t.top+t.height)
                       ));

    v.append(sf::Vertex(sf::Vector2f(c.left, c.top+c.height),
                        sf::Vector2f(t.left, t.top+t.height)
                       ));

    return 0;
}


}//end namespace bali
