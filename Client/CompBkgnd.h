#ifndef CompBackgnd_h_
#define CompBackgnd_h_


namespace bali{

class CompBackgnd : public Component
{
public:
    CompBackgnd(){}
    ~CompBackgnd(){}
    uint32_t initialize()
    {
//        initializeLayer(i, newLayer);
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
    sf::VertexArray backgndLayer;
};

}//end namespace bali

#endif

