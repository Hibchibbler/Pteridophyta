#include "CompDynamicLayer.h"
#include "ContextClient.h"
namespace bali{

CompDynamicLayer::CompDynamicLayer()
{
}

CompDynamicLayer::~CompDynamicLayer()
{
}

//General Component Functionality
uint32_t CompDynamicLayer::initialize(Context& cc)
{
    layer = sf::VertexArray(sf::PrimitiveType::Quads);
    return 0;
}

uint32_t CompDynamicLayer::doWindowEvent(Context& cc, sf::Event & event)
{
    return 0;
}

uint32_t CompDynamicLayer::doLocalInputs(Context& cc)
{
    return 0;
}

uint32_t CompDynamicLayer::doUpdate(Context& cc)
{
    return 0;
}

uint32_t CompDynamicLayer::doDraw(Context& cc)
{
    return 0;
}

uint32_t CompDynamicLayer::cleanup(Context& cc)
{
    return 0;
}

}//end namespace bali
