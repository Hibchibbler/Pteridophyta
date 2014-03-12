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

    SPlayer getSpectatorByCid(sf::Uint32 cid)
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

    void removeSpectatorByCid(sf::Uint32 cid)
    {
        for (auto s = spectators.begin(); s != spectators.end();s++)
        {
            if ((*s)->connectionId == cid)
            {
                spectators.erase(s);
                break;
            }
        }
    }


    std::vector<SPlayer> players;
    std::vector<SPlayer> spectators;
    Player player;
private:
};
};//end namespace bali

#endif

