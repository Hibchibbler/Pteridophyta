#ifndef Util_h_
#define Util_h_

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);


//this algorithm assumes '0' as first index
//
sf::Vector2i indexToPosition(int index, int tiles_wide, int tile_width, int tile_height);
uint32_t positionToIndex(sf::Vector2f pos, int tiles_wide, int tile_width, int tile_height);
#endif // Util_h_
