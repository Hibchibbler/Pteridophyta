#ifndef ManagerPlayer_h_
#define ManagerPlayer_h_

#include "Player.h"
#include <vector>
#include <memory>

namespace bali{
class ManagerPlayer
{
public:
    uint32_t processLocalCommands()
    {
        player.processCommands(nullptr);
        return 0;
    }

    uint32_t processAllCommands()
    {
        for (auto&p : players)
        {
            p->processCommands(nullptr);
        }
        return 0;
    }
    void setPlayerStartInfo(std::string name, std::string  pass, uint32_t serverPort, std::string serverIP)
    {
        player.name = name;
        player.pass = pass;
        player.server_port = serverPort;
        player.server_ip = serverIP;
    }

    std::string getPlayerName()
    {
        return player.name;
    }

    void addPlayer(Player::Ptr player){
        players.push_back(player);
    }

    Player::Ptr getPlayerByCid(uint32_t cid)
    {
        for (const auto& p: players)
        {
            if (p->connectionId == cid)
            {
                return p;
            }
        }

        return Player::Ptr(nullptr);
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

    bool isAllPlayersReady()
    {
        for (auto p = players.begin(); p != players.end();p++)
        {
            if (!(*p)->isReady())
                return false;
        }
        return true;
    }

    uint32_t getNumPlayers()
    {
        return players.size();
    }

    std::vector<Player::Ptr> players;//Server Side Player State
    Player                   player; //Client Side Player State
private:
};
};//end namespace bali

#endif

