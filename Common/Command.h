#ifndef Command_h_
#define Command_h_

namespace bali{

class Command
{
public:
    Command()=default;
    Command(uint32_t f){mjFunction=f;}
    virtual ~Command()=default;
    uint32_t getFunction(){return mjFunction;}
    void     setFunction(uint32_t f){mjFunction=f;}
    uint32_t getMjFunction(){return mjFunction;}
    void     setMjFunction(uint32_t f){mjFunction=f;}
    uint32_t getMnFunction(){return mnFunction;}
    void     setMnFunction(uint32_t f){mnFunction=f;}
protected:
    uint32_t mjFunction;
    uint32_t mnFunction;

};

}//end namespace bali

#endif

