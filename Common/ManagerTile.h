#ifndef ManagerTile_h_
#define ManagerTile_h_

#include <SFML\graphics.hpp>


namespace bali{



class ManagerMap;
class ManagerTile
{
public:
    struct SubSprite{
        SubSprite(sf::IntRect irect_, uint32_t tsi_, uint32_t gid_=0){
            irect = irect_;
            tsi = tsi_;
            gid = gid_;
        }
        sf::IntRect irect;
        uint32_t tsi;
        uint32_t gid;
    };


    ManagerTile();
    ~ManagerTile();
    bool initialize(ManagerMap& mapMan);

    SubSprite getPlayer(){
        return SubSprite(sf::IntRect(0,0,32,48), 1);
    }
    SubSprite getStar(){
        return SubSprite(sf::IntRect(0,0,16,16), 2);
    }

};


}//namespace bali

#endif

