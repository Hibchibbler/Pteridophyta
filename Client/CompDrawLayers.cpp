#include "CompDrawLayers.h"
#include "Context.h"
#include "Game.h"
#include "Stage.h"


namespace bali{

CompDrawLayers::CompDrawLayers(Stage* stage)
    : Component(stage)
{
}

CompDrawLayers::~CompDrawLayers()
{
}

ReturnVal CompDrawLayers::initialize()
{
    Context& ctx = stage->game->ctx;
    //Load all layers. We assume layers contain static content.
    uint32_t numLayers = ctx.mm.layers.size();
    for (int i = 0;i < numLayers;i++)
    {
        layers.push_back(sf::VertexArray(sf::PrimitiveType::Quads));
        ctx.mm.initializeLayer(i, layers.back());
    }
    return ReturnVal();
}

ReturnVal CompDrawLayers::doWindowEvent(sf::Event & event)
{
    return ReturnVal();
}

ReturnVal CompDrawLayers::doLocalInputs()
{
    return ReturnVal();
}

ReturnVal CompDrawLayers::doUpdate()
{
    return ReturnVal();
}

ReturnVal CompDrawLayers::doDraw()
{
    Context& ctx = stage->game->ctx;

    //Background
    uint32_t gid, tsi;
    gid = ctx.mm.getFirstNonZeroGidInLayer(currentLayer);
    tsi = ctx.mm.getTileSetIndexByGid(gid);
    ctx.window.draw(layers[currentLayer], &ctx.mm.tileSets[tsi].tex);

    return ReturnVal();
}

ReturnVal CompDrawLayers::cleanup()
{
    return ReturnVal();
}

}//end namespace bali
