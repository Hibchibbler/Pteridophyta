#ifndef CompLevelLayer_h_
#define CompLevelLayer_h_

#include <SFGUI/sfgui.hpp>
#include "Component.h"

namespace bali{
class Context;

class CompDrawLayers : public Component
{
public:
    CompDrawLayers(Stage* stage);
    ~CompDrawLayers();
    uint32_t initialize(Context& ctx);
    uint32_t doWindowEvent(Context& ctx, sf::Event & event);
    uint32_t doLocalInputs(Context& ctx);
    uint32_t doUpdate(Context& ctx);
    uint32_t doDraw(Context& ctx);
    uint32_t cleanup(Context& ctx);
    uint32_t processCommands(void* arg){};
    void setDrawLayer(uint32_t l){ currentLayer=l;}
private:
    uint32_t currentLayer=0;
    std::vector<sf::VertexArray> layers;
};

}//end namespace bali

#endif

