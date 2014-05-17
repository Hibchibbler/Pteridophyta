#ifndef ReturnVal_h_
#define ReturnVal_h_

namespace bali{

    struct ReturnVal{
        enum class Source{
            GAME,
            STAGE,
            COMPONENT
        };
        enum class Code{
            SUCCESS,
            ULTRASUCCESS,
            ERROR_MEMORY_ALLOC,
            ERROR_ASSET_MISSING,
            ERROR_PARSE,
            ERROR_COMM,
            ERROR_GRAPHICS,
            ERROR_INPUT,
            ERROR_WEIRD
        };

        Source      source;
        Code        code;
        uint32_t    flags;

    };

}//end namespace bali

#endif

