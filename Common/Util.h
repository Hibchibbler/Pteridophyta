#ifndef Util_h_
#define Util_h_

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

namespace bali{

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);


//this algorithm assumes '0' as first index
//
sf::Vector2i indexToPosition(int index, int tiles_wide, int tile_width, int tile_height);
uint32_t positionToIndex(sf::Vector2f pos, int tiles_wide, int tile_width, int tile_height);


//
struct Quad{
    sf::Vector2f v1;
    sf::Vector2f v2;
    sf::Vector2f v3;
    sf::Vector2f v4;
};



uint32_t addStraightQuad(sf::VertexArray& v, sf::FloatRect c, sf::IntRect t);
uint32_t addRotQuad(sf::VertexArray & v, sf::FloatRect p, sf::IntRect t, float angleRAD);
Quad constructQuad(sf::FloatRect r);
Quad rotateQuad(Quad q, sf::Vector2f pivot, float angle);
uint32_t addQuadToVertexArray(sf::VertexArray & v, Quad q, sf::IntRect t);


}//end namespace bali
#endif // Util_h_
