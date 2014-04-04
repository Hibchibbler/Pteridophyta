#include "CompLevelLayer.h"
#include "ContextClient.h"

namespace bali{

CompLevelLayer::CompLevelLayer()
{
}

CompLevelLayer::~CompLevelLayer()
{
}

uint32_t CompLevelLayer::initialize(Context& cc)
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

uint32_t CompLevelLayer::doWindowEvent(Context& cc, sf::Event & event)
{
    return 0;
}

uint32_t CompLevelLayer::doLocalInputs(Context& cc)
{
    return 0;
}

uint32_t CompLevelLayer::doUpdate(Context& cc)
{
    return 0;
}

uint32_t CompLevelLayer::doDraw(Context& c)
{
    ContextClient& cc = *((ContextClient*)&c);

    //Background
    uint32_t gid, tsi;
    gid = cc.mm.getFirstNonZeroGidInLayer(currentLayer);
    tsi = cc.mm.getTileSetIndexByGid(gid);
    cc.window.draw(layers[currentLayer], &cc.mm.map.tileSets[tsi].tex);

    return 0;
}

uint32_t CompLevelLayer::cleanup(Context& cc)
{
    return 0;
}

}//end namespace bali
