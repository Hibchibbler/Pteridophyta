#ifndef GameStage_h_
#define GameStage_h_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Comm.h"
#include "Component.h"
#include "Commandable.h"
#include "CommandStage.h"
#include "ReturnVal.h"

namespace bali
{
    class Command;
    class Game;

    //Stage represents an discrete, unique block of functionality. It represents the most course grain
    // unit of game functionality.
    //Splash Screen, Lobby, Main game view, and credits are examples of what represents a Stage.
    class Stage : public Commandable
    {
    public:
        typedef std::shared_ptr<Stage> Ptr;


    public:
        Stage(Game* game, uint32_t uid);

        virtual ~Stage();
        //
        //Derived class is responsible for
        //calling Stage::initialized() from
        //their Stage::initialize() routine, when initialization
        //is complete.
        //
        virtual ReturnVal initialize()=0;

        //
        //doRemoteEvent is responsible for receiving data from server.
        //
        virtual ReturnVal doRemoteEvent(CommEvent & event)=0;

        virtual ReturnVal doWindowEvent(sf::Event & event)=0;
        virtual ReturnVal doLocalInputs()=0;

        //
        //doUpdate
        //
        virtual ReturnVal doUpdate()=0;

        virtual ReturnVal doDraw()=0;
        virtual ReturnVal cleanup()=0;

        Game* getOwner();
        void setId(uint32_t id);
        uint32_t getId();
        uint32_t isDone();
        //
        //isError() if returns > 0 then error, and value is defined
        //by derived stage
        //returns 0 if no error
        //
        uint32_t isError();
        uint32_t isInit();
        void initialized(){init=1;}
        void finished(uint32_t e){err=e;done=1;}
        uint32_t id;
        uint32_t done;
        uint32_t err;
        uint32_t init;

        //reference to owner
        Game* game;

        std::vector<std::shared_ptr<Component>> components;
        std::map<uint32_t, std::vector<Commandable*> > subscribers;

        void submitToComponents(std::shared_ptr<Command> cmd);
        uint32_t subscribe(uint32_t function, Commandable* c);


        //void submitCommand(CommandStage cmd){}
        //uint32_t processCommands(void* arg){}
        //std::queue<CommandStage> commands;
    };

};


#endif
