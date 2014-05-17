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
    ReturnVal initialize();
    ReturnVal doWindowEvent(sf::Event & event);
    ReturnVal doLocalInputs();
    ReturnVal doUpdate();
    ReturnVal doDraw();
    ReturnVal cleanup();
    uint32_t processCommands(void* arg){};
    void setDrawLayer(uint32_t l){ currentLayer=l;}
private:
    uint32_t currentLayer=0;
    std::vector<sf::VertexArray> layers;
};

}//end namespace bali

#endif

