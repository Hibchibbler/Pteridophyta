#include "CompDrawLayers.h"
#include "ContextClient.h"

namespace bali{

CompDrawLayers::CompDrawLayers()
{
}

CompDrawLayers::~CompDrawLayers()
{
}

uint32_t CompDrawLayers::initialize(Context& cc)
{
    //Load all layers. We assume layers contain static content.
    uint32_t numLayers = cc.mm.map.layers.size();
    for (int i = 0;i < numLayers;i++)
    {
        layers.push_back(sf::VertexArray(sf::PrimitiveType::Quads));
        cc.mm.initializeLayer(i, layers.back());
    }
    return 0;
}

uint32_t CompDrawLayers::doWindowEvent(Context& cc, sf::Event & event)
{
    return 0;
}

uint32_t CompDrawLayers::doLocalInputs(Context& cc)
{
    return 0;
}

uint32_t CompDrawLayers::doUpdate(Context& cc)
{
    return 0;
}

uint32_t CompDrawLayers::doDraw(Context& c)
{
    ContextClient& cc = *((ContextClient*)&c);

    //Background
    uint32_t gid, tsi;
    gid = cc.mm.getFirstNonZeroGidInLayer(currentLayer);
    tsi = cc.mm.getTileSetIndexByGid(gid);
    cc.window.draw(layers[currentLayer], &cc.mm.map.tileSets[tsi].tex);

    return 0;
}

uint32_t CompDrawLayers::cleanup(Context& cc)
{
    return 0;
}

}//end namespace bali
