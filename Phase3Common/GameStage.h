#ifndef GameStage_h_
#define GameStage_h_

#include <SFML/Graphics.hpp>
#include <string>
#include "common.h"
#include "Comm.h"

#define CONTEXT_ELEMENTS 8

namespace bali
{
    class Game;

//    class StageContext{
//    public:
//
//        StageContext(){
//
//        }
//
//        std::string name;
//        std::string pass;
//        std::string port;
//        std::string ip;
//
//        std::string strval;
//        sf::Uint32 uint32val;
//
//    };



    //GameStage represents an discrete, unique block of functionality. It represents the most course grain
    // unit of game functionality.
    //Splash Screen, Lobby, Main game view, and credits are examples of what represents a GameStage.
    //Before a GameStage is transitioned into, the client-code will provide stage specific data via setPrologue
    //After a GameStage is transitioned out, client-code can examine stage specific results via getEpilogue
    //The data provided to setPrologue, and the data retrieved from getEpiloque is a Summary.
    class GameStage
    {
    public:
        GameStage(Game & game, sf::Uint32 uid);
        virtual ~GameStage();
        virtual sf::Uint32 initialize()=0;
        virtual sf::Uint32 doRemoteEvents(CommEvent & cevent)=0;
        virtual sf::Uint32 doWindowEvents(sf::Event & wevent)=0;
        virtual sf::Uint32 doLocalInputs()=0;
        virtual sf::Uint32 doLoop()=0;
        virtual sf::Uint32 doDraw()=0;
        virtual sf::Uint32 cleanup()=0;

        Game & getOwner();
        void setId(sf::Uint32 id);
        sf::Uint32 getId();
        sf::Uint32 isDone();
        sf::Uint32 isError();
        sf::Uint32 isInit();

        void initialized(){init=1;}
        void finished(sf::Uint32 e){err=e;done=1;}

        //reference to owner
        Game & g;

        sf::Uint32 id;
        sf::Uint32 done;
        sf::Uint32 err;
        sf::Uint32 init;


    };

};


#endif
