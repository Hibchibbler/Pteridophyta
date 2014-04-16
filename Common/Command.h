#ifndef Command_h_
#define Command_h_

namespace bali{

class Command
{
public:
    Command(uint32_t f)
    {
        function=f;
    }
private:
    uint32_t function;
};


}//end namespace bali

#endif

