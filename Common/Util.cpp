#include "Util.h"
#include <SFML\System\Vector2.hpp>
#include <sstream>
namespace bali{

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


Quad rotateQuad(Quad q, sf::Vector2f pivot, float angle)
{
    ///Angles are measured counter?/clockwise?

    ///Translate to Origin
    q.v1.x -= pivot.x;
    q.v1.y -= pivot.y;
    q.v2.x -= pivot.x;
    q.v2.y -= pivot.y;
    q.v3.x -= pivot.x;
    q.v3.y -= pivot.y;
    q.v4.x -= pivot.x;
    q.v4.y -= pivot.y;

    ///Rotate
    float x1 = ((q.v1.x) * cos(angle) - (q.v1.y) * sin(angle));
    float y1 = ((q.v1.x) * sin(angle) + (q.v1.y) * cos(angle));
    float x2 = ((q.v2.x) * cos(angle) - (q.v2.y) * sin(angle));
    float y2 = ((q.v2.x) * sin(angle) + (q.v2.y) * cos(angle));
    float x3 = ((q.v3.x) * cos(angle) - (q.v3.y) * sin(angle));
    float y3 = ((q.v3.x) * sin(angle) + (q.v3.y) * cos(angle));
    float x4 = ((q.v4.x) * cos(angle) - (q.v4.y) * sin(angle));
    float y4 = ((q.v4.x) * sin(angle) + (q.v4.y) * cos(angle));

    ///Translate back into position
    q.v1.x = x1 + pivot.x;
    q.v1.y = y1 + pivot.y;
    q.v2.x = x2 + pivot.x;
    q.v2.y = y2 + pivot.y;
    q.v3.x = x3 + pivot.x;
    q.v3.y = y3 + pivot.y;
    q.v4.x = x4 + pivot.x;
    q.v4.y = y4 + pivot.y;

    return q;
}

uint32_t addQuadToVertexArray(sf::VertexArray & v, Quad q, sf::IntRect t)
{
    v.append(sf::Vertex(sf::Vector2f(q.v1.x,q.v1.y),
                        sf::Vector2f(t.left, t.top)
                       ));

    v.append(sf::Vertex(sf::Vector2f(q.v2.x,q.v2.y),
                        sf::Vector2f(t.left+t.width, t.top)
                       ));

    v.append(sf::Vertex(sf::Vector2f(q.v3.x,q.v3.y),
                        sf::Vector2f(t.left+t.width, t.top+t.height)
                       ));

    v.append(sf::Vertex(sf::Vector2f(q.v4.x,q.v4.y),
                        sf::Vector2f(t.left, t.top+t.height)
                       ));


    return 0;
}

Quad constructQuad(sf::FloatRect r)
{
    Quad q;
    q.v1.x = r.left;          q.v1.y = r.top;
    q.v2.x = r.left+r.width;  q.v2.y = r.top;
    q.v3.x = r.left+r.width;  q.v3.y = r.top + r.height;
    q.v4.x = r.left;          q.v4.y = r.top + r.height;
    return q;

}

uint32_t addRotQuad(sf::VertexArray & v, sf::FloatRect p, sf::IntRect t, float angleRAD)
{
    Quad q = constructQuad(p);
    //rotateQuad(q,sf::Vector2f(p.left+p.width/2.0, p.top+p.height/2.0), angle);
    rotateQuad(q,sf::Vector2f(200,200), angleRAD);
    addQuadToVertexArray(v,q,t);

    return 0;
}


}//end namespace bali
