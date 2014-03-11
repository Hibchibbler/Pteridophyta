#ifndef ManagerPlayer_h_
#define ManagerPlayer_h_

#include "Player.h"
#include <vector>
#include <memory>

namespace bali{
class ManagerPlayer
{
public:
    SPlayer getPlayerByCid(sf::Uint32 cid)
    {
        for (auto p = players.begin();
             p != players.end();
             p++)
        {
            if ((*p)->connectionId == cid)
            {
                    return *p;
            }
        }

        return SPlayer();
    }

    std::vector<SPlayer> players;
    Player player;
private:
};
};//end namespace bali

#endif

