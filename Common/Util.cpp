#include "Util.h"
#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


//this algorithm assumes '0' as first index
//
sf::Vector2i indexToPosition(int index, int tiles_wide, int tile_width, int tile_height)
{
    uint32_t r = (index % tiles_wide) * tile_width;
    uint32_t c = (index / tiles_wide) * tile_height;
    return sf::Vector2i(r,c);
}
uint32_t positionToIndex(sf::Vector2f pos, int tiles_wide, int tile_width, int tile_height)
{
    int w,h;
    w = tile_width;
    h = tile_height;
    int gridCoordX = (((int)pos.x / w) * w);
    int gridCoordY = (((int)pos.y / h) * h);
    int mapCoordX = gridCoordX / w;
    int mapCoordY = gridCoordY / h;
    return mapCoordX + (mapCoordY*tiles_wide);
}

uint32_t addStraightQuad(sf::VertexArray& v, sf::FloatRect c, sf::IntRect t)
{
    v.append(sf::Vertex(sf::Vector2f(c.left, c.top),
                        sf::Vector2f(t.left, t.top)
                        ));

    v.append(sf::Vertex(sf::Vector2f(c.left+c.width, c.top),
                        sf::Vector2f(t.left+t.width, t.top)
                        ));

    v.append(sf::Vertex(sf::Vector2f(c.left+c.width, c.top+c.height),
                        sf::Vector2f(t.left+t.width, t.top+t.height)
                        ));

    v.append(sf::Vertex(sf::Vector2f(c.left, c.top+c.height),
                        sf::Vector2f(t.left, t.top+t.height)
                        ));

    return 0;
}
