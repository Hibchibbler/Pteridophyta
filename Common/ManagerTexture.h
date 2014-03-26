#ifndef ManagerTexture_h_
#define ManagerTexture_h_

#include <SFML\graphics.hpp>


namespace bali{

class TileSet
{
public:
    uint32_t load(std::string fn, std::string n, uint32_t tw, uint32_t th, uint32_t w, uint32_t h){
        name = n;
        width = w;
        height = h;
        tileWidth = tw;
        tileHeight = th;

        img.loadFromFile(fn);
        img.createMaskFromColor(sf::Color::Cyan,0);
        tex.loadFromImage(img);
        tex.setSmooth(false);
        sprite.setTexture(tex);
        return 0;
    }
    uint32_t unload(){
        return 0;
    }
    sf::Image img;
    sf::Texture tex;
    sf::Sprite sprite;

    std::string name;
    uint32_t width;
    uint32_t height;
    uint32_t tileWidth;
    uint32_t tileHeight;
};

class ManagerMap;
class ManagerTexture
{
public:
    ManagerTexture();
    ~ManagerTexture();
    bool initialize(ManagerMap& mapMan);
    bool load(char* cfgfn);


    std::map<std::string, TileSet> tileSets;
};


}//namespace bali

#endif

