#ifndef CompLevelLayer_h_
#define CompLevelLayer_h_


namespace bali{

class CompLevelLayer : public Component
{
public:
    CompLevelLayer(){}
    ~CompLevelLayer(){}
    uint32_t initialize()
    {

        return 0;
    }
    uint32_t doUpdate()
    {
        return 0;
    }
    uint32_t doDraw()
    {
        return 0;
    }

    uint32_t cleanup()
    {
        return 0;
    }
private:
    sf::VertexArray layer;
};

}//end namespace bali

#endif

