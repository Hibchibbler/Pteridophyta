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
    uint32_t initialize(Context& cc);
    uint32_t doWindowEvent(Context& cc, sf::Event & event);
    uint32_t doLocalInputs(Context& cc);
    uint32_t doUpdate(Context& cc);
    uint32_t doDraw(Context& cc);
    uint32_t cleanup(Context& cc);
    uint32_t processCommands(){};
    void setDrawLayer(uint32_t l){ currentLayer=l;}
private:
    uint32_t currentLayer=0;
    std::vector<sf::VertexArray> layers;
};

}//end namespace bali

#endif

