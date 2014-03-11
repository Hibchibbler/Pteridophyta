#ifndef Manager_h_
#define Manager_h_

namespace bali{
namespace mgr{

class Manager{
public:
    bool initialize()=0;
    bool load()=0;
    bool cleanup()=0;

};


}
}

#endif

