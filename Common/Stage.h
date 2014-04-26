#ifndef GameStage_h_
#define GameStage_h_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Comm.h"
#include "Component.h"
#include "Commandable.h"
#include "CommandStage.h"


namespace bali
{
    class Command;
    class Game;

    //Stage represents an discrete, unique block of functionality. It represents the most course grain
    // unit of game functionality.
    //Splash Screen, Lobby, Main game view, and credits are examples of what represents a Stage.
    class Stage : public Commandable<CommandStage>
    {
    public:

        Stage(Game* game, uint32_t uid);

        virtual ~Stage();
        //
        //Derived class is responsible for
        //calling Stage::initialized() from
        //their Stage::initialize() routine, when initialization
        //is complete.
        //
        virtual uint32_t initialize()=0;

        //
        //doRemoteEvent is responsible for receiving data from server.
        //
        virtual uint32_t doRemoteEvent(CommEvent & event)=0;

        virtual uint32_t doWindowEvent(sf::Event & event)=0;
        virtual uint32_t doLocalInputs()=0;

        //
        //doUpdate
        //
        virtual uint32_t doUpdate()=0;

        virtual uint32_t doDraw()=0;
        virtual uint32_t cleanup()=0;

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
        Game* g;

        std::vector<std::shared_ptr<Component>> components;
        //void submitCommand(CommandStage cmd){}
        //uint32_t processCommands(){}
        //std::queue<CommandStage> commands;
    };

};


#endif
