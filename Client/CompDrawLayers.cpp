#include "CompDrawLayers.h"
#include "Context.h"

namespace bali{

CompDrawLayers::CompDrawLayers(Stage* stage)
    : Component(stage)
{
}

CompDrawLayers::~CompDrawLayers()
{
}

uint32_t CompDrawLayers::initialize(Context& ctx)
{
    //Load all layers. We assume layers contain static content.
    uint32_t numLayers = ctx.mm.layers.size();
    for (int i = 0;i < numLayers;i++)
    {
        layers.push_back(sf::VertexArray(sf::PrimitiveType::Quads));
        ctx.mm.initializeLayer(i, layers.back());
    }
    return 0;
}

uint32_t CompDrawLayers::doWindowEvent(Context& ctx, sf::Event & event)
{
    return 0;
}

uint32_t CompDrawLayers::doLocalInputs(Context& ctx)
{
    return 0;
}

uint32_t CompDrawLayers::doUpdate(Context& ctx)
{
    return 0;
}

uint32_t CompDrawLayers::doDraw(Context& ctx)
{
    //Background
    uint32_t gid, tsi;
    gid = ctx.mm.getFirstNonZeroGidInLayer(currentLayer);
    tsi = ctx.mm.getTileSetIndexByGid(gid);
    ctx.window.draw(layers[currentLayer], &ctx.mm.tileSets[tsi].tex);

    return 0;
}

uint32_t CompDrawLayers::cleanup(Context& ctx)
{
    return 0;
}

}//end namespace bali
