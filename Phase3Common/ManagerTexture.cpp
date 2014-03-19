#include "ManagerTexture.h"
#include "ManagerMap.h"
#include <iostream>
#include <string>
namespace bali{

ManagerTexture::ManagerTexture()
{


}

ManagerTexture::~ManagerTexture()
{

}
bool ManagerTexture::initialize(ManagerMap& mapMan)
{
    for (auto& m : mapMan.maps){
        for (auto& t : m->tileSets){
            std::cout << "Loading image " << t.image.source<<std::endl;
            spriteSheets.push_back(Texture());
            spriteSheets.back().load(t.image.source, t.name, atoi(t.tilewidth.c_str()), atoi(t.tileheight.c_str()), atoi(t.image.width.c_str()), atoi(t.image.height.c_str()));
        }
    }
    return false;
}

bool ManagerTexture::load(char* cfgfn)
{
//    cfg::ConfigurationLoader::load(cfgfn,&configuration);
//    tmx::TMXLoader::load(configuration.client.maps[0].name.c_str(), &tmxMap);

    return false;
}

//int ManagerTexture::load()
//{
////    font.loadFromFile("Assets\\digital-7mono.ttf");
////    spriteSheet.load("Assets\\FloorTiles.png");
////    smallExplosionSheet.load("Assets\\smallExplosion.png");
////    bigExplosionSheet.load("Assets\\bigExplosion.png");
//
//    spriteSheet1.load("Assets\\IsoHex.png");
//    return 0;
//}
//
//
//sf::Font & ManagerTexture::getFont()
//{
//    return font;
//}
//
//
//sf::Sprite & ManagerTexture::getSprite(int i)
//{
//    switch (i)
//    {
////    case ImageType::Projectile1:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(448,64,32,32));
////        return spriteSheet.sprite;
////    case ImageType::ProjectileShadow:
////        return spriteSheet.sprite;
////    case ImageType::ProjectileHealRay:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(448,0,64,64));
////        return spriteSheet.sprite;
////    case ImageType::ProjectileDeathRay:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(384,0,64,64));
////        return spriteSheet.sprite;
////    case ImageType::FloorWall1:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(0,0,128,128));
////        return spriteSheet.sprite;
////    case ImageType::Floor1:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(128,0,128,128));
////        return spriteSheet.sprite;
////    case ImageType::Floor2:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(256,0,128,128));
////        return spriteSheet.sprite;
////    case ImageType::Base1:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(0,128,128,128));
////        return spriteSheet.sprite;
////    case ImageType::Base2:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(128,128,128,128));
////        return spriteSheet.sprite;
////    case ImageType::Generator1:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(0,256,128,128));
////        return spriteSheet.sprite;
////    case ImageType::Generator2:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(128,256,128,128));
////        return spriteSheet.sprite;
////    case ImageType::FogOfWar15:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(1,515,128,128));
////        return spriteSheet.sprite;
////    case ImageType::FogOfWar30:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(131,515,128,128));
////        return spriteSheet.sprite;
////    case ImageType::FogOfWar45:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(261,515,128,128));
////        return spriteSheet.sprite;
////    case ImageType::FogOfWar60:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(391,515,128,128));
////        return spriteSheet.sprite;
////    case ImageType::FogOfWar75:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(521,515,128,128));
////        return spriteSheet.sprite;
////    case ImageType::Ghost:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(256,382,64,64));
////        return spriteSheet.sprite;
////
////
////    case ImageType::Minion1:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(512,1,64,64));
////        return spriteSheet.sprite;
////    case ImageType::Minion2:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(578,1,64,64));
////        return spriteSheet.sprite;
////    case ImageType::Minion3:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(644,1,69,69));
////        return spriteSheet.sprite;
////    case ImageType::Minion4:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(715,1,69,69));
////        return spriteSheet.sprite;
////
////    case ImageType::Minion5:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(512,67,64,64));
////        return spriteSheet.sprite;
////    case ImageType::Minion6:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(578,67,64,64));
////        return spriteSheet.sprite;
////    case ImageType::Minion7:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(644,72,69,69));
////        return spriteSheet.sprite;
////    case ImageType::Minion8:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(715,72,69,69));
////        return spriteSheet.sprite;
////
////    case ImageType::Dash1:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(0,447,512,65));
////        return spriteSheet.sprite;
////    case ImageType::ExplosionSmall:
////        return smallExplosionSheet.sprite;
////    case ImageType::ExplosionBig:
////        return bigExplosionSheet.sprite;
////    case ImageType::TankBlue:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(256,128,73,116));
////        return spriteSheet.sprite;
////    case ImageType::TankRed:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(384,128,73,116));
////        return spriteSheet.sprite;
////    case ImageType::TurretBlue:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(331,128,47,176));
////        return spriteSheet.sprite;
////    case ImageType::TurretRed:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(459,128,47,176));
////        return spriteSheet.sprite;
////    case ImageType::Waypoint1_1:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(522,361,128,128));
////        return spriteSheet.sprite;
////    case ImageType::Waypoint1_2:
////        spriteSheet.sprite.setTextureRect(sf::IntRect(653,361,128,128));
////        return spriteSheet.sprite;
//    }
//}
//
//
//sf::Texture & ManagerTexture::getTexture(int i)
//{
//    switch (i)
//    {
////    case 0:
////        return spriteSheet.tex;
////    case 1:
////        return smallExplosionSheet.tex;
////    case 2:
////        return bigExplosionSheet.tex;
////    default:
////        return bigExplosionSheet.tex;
//    };
//}



}//end namespace bali
