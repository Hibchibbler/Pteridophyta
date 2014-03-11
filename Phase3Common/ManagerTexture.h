#ifndef ManagerTexture_h_
#define ManagerTexture_h_

#include <SFML\graphics.hpp>


namespace bali{

class ImageTexite
{
public:
    sf::Uint32 load(std::string fn, std::string n, sf::Uint32 tw, sf::Uint32 th, sf::Uint32 w, sf::Uint32 h){
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
    sf::Uint32 unload(){
        return 0;
    }
    sf::Image img;
    sf::Texture tex;
    sf::Sprite sprite;

    std::string name;
    sf::Uint32 width;
    sf::Uint32 height;
    sf::Uint32 tileWidth;
    sf::Uint32 tileHeight;
};

class ManagerMap;
class ManagerTexture
{
public:
    ManagerTexture();
    ~ManagerTexture();
    bool initialize(ManagerMap& mapMan);
    bool load(char* cfgfn);

    std::vector<ImageTexite> spriteSheets;
};


}//namespace bali

#endif

