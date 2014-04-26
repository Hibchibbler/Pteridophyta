#ifndef Command_h_
#define Command_h_

namespace bali{

class Command
{
public:
    virtual ~Command()=default;
    uint32_t getFunction(){return function;}
    void     setFunction(uint32_t f){function=f;}
protected:
    uint32_t function;

};




class CmdPlayer : public Command
{
public:
    enum class Functions{
        MOVEBEGIN,
        MOVEEND,
        JUMPBEGIN,
        JUMPEND,
        ATTACKBEGIN,
        ATTACKEND
    };

    union u{
        struct MoveBegin{
            uint32_t direction;
        }mb;
        struct MoveEnd{

        }me;
        struct JumpBegin{

        }jb;
        struct JumpEnd{

        }je;
        struct AttackBegin{

        }ab;
        struct AttackEnd{

        }ae;
    };
};



}//end namespace bali

#endif

