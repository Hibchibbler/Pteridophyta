#ifndef ManagerPlayer_h_
#define ManagerPlayer_h_

#include "Player.h"
#include <vector>
#include <memory>

namespace bali{
class ManagerPlayer
{
public:
    void addPlayer(SPlayer player){
        players.push_back(player);
    }

    SPlayer getPlayerByCid(uint32_t cid)
    {
        for (const auto& p: players)
        {
            if (p->connectionId == cid)
            {
                return p;
            }
        }

        return SPlayer();
    }

    bool removePlayerByCid(uint32_t cid)
    {
        for (auto p = players.begin(); p != players.end();p++)
        {
            if ((*p)->connectionId == cid)
            {
                players.erase(p);
                return true;
            }
        }
        return false;
    }

//    void removeSpectatorByCid(uint32_t cid)
//    {
//        for (auto s = spectators.begin(); s != spectators.end();s++)
//        {
//            if ((*s)->connectionId == cid)
//            {
//                spectators.erase(s);
//                break;
//            }
//        }
//    }


    std::vector<SPlayer> players;
//    std::vector<SPlayer> spectators;
    Player player;
private:
};
};//end namespace bali

#endif

