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
//        uint32_t uint32val;
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
        GameStage(Game & game, uint32_t uid);
        virtual ~GameStage();

        //
        //Derived class is responsible for
        //calling GameStage::initialized() from
        //their GameStage::initialize() routine, when initialization
        //is complete.
        //
        virtual uint32_t initialize()=0;

        //
        //doRemoteEvent is responsible for receiving data from server.
        //
        virtual uint32_t doRemoteEvents(CommEvent & event)=0;

        virtual uint32_t doWindowEvents(sf::Event & wevent)=0;
        virtual uint32_t doLocalInputs()=0;

        //
        //doLoop is responsible for sending data to server.
        //
        virtual uint32_t doLoop()=0;

        virtual uint32_t doDraw()=0;
        virtual uint32_t cleanup()=0;

        Game & getOwner();
        void setId(uint32_t id);
        uint32_t getId();
        uint32_t isDone();
        uint32_t isError();
        uint32_t isInit();

        void initialized(){init=1;}
        void finished(uint32_t e){err=e;done=1;}

        //reference to owner
        Game & g;

        uint32_t id;
        uint32_t done;
        uint32_t err;
        uint32_t init;


    };

};


#endif
