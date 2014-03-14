
/**********************************************************************************
Comm.h

Copyright 2012, 2013, 2014
Daniel Ferguson
**********************************************************************************/

#ifndef Comm_h_
#define Comm_h_

#include <SFML/Network.hpp>
#include <memory>
#include <queue>
#include <vector>


namespace bali
{
    //class Connection contains information that is specific to a connection between two points.
    // * Queue's for reads and writes.
    // * Mutexes to synchronize access to the queues.
    // * The socket used to read and write to the connection
    // * A unique identifier used to identify this connection. This identifier is only
    //   unique to an instance of Comm.
    class Connection
    {
    public:
        Connection(){
            IsConnected = false;
            error = false;
            /*Socket = NULL;
            SendMutex = NULL;
            RecvMutex = NULL;*/
        }

        bool IsConnected;
        bool error;
        sf::TcpSocket Socket;
        sf::Uint32 connectionId;
        std::queue<sf::Packet> RecvQueue;
        std::queue<sf::Packet> SendQueue;
        sf::Mutex SendMutex;
        sf::Mutex RecvMutex;
        sf::SocketSelector selector;
    private:

    };
    class Comm;
    struct LooperListenerArg
	{
        LooperListenerArg(Comm* c){
            comm = c;
        }
		Comm* comm;
	};

	struct LooperClientHandlerArg
	{
		typedef unsigned char byte;
		LooperClientHandlerArg(Comm* cm, const std::shared_ptr<Connection> & cn)
		{
			comm = cm;
			conn = cn;
		}
		Comm* comm;
		std::shared_ptr<Connection> conn;

	};

	struct LooperClientHandlerContext
	{////FOLLOW UP ON  THIS
        LooperClientHandlerContext(Comm* cm, const std::shared_ptr<Connection> & cn){
            comm = cm;
            conn = cn;
        }
        Comm* comm;
		std::shared_ptr<Connection> conn;
        void LooperClientHandler();
	};

    //CommEvent is a structure containing
    // information, pertaining to a particular event, that is passed to the user.
    struct CommEventType{
        //** these convey the connectionid to the game via the packet payload.
        enum CET{
            Connected,//**
            Established,
            Disconnect,//**
            Data,
            Sent,
            Error
        };
    };

    //Note
    //connectionId is used with the Comm interface to send messages to the serve, by way of a particular connection.
    //You specify the connectionId of the connection. The connectionId is local only. Not transmitted. There is no
    //relationship between the connectionId's on the server, and those on the client.
    //
    class CommEvent
    {
    public:

        CommEvent(){
            connectionId = -1;
        }
        sf::Packet packet;
        sf::Uint32 connectionId;
    private:
    };


    class Comm
    {
    public:
        Comm()
            :
        LooperMasterThread(Comm::LooperMaster,this){
            NotDone = true;
            TotalConnectCount=0;


            for (int c = 0;c <15;c++)
            {
                Established.push_back(std::shared_ptr<Connection>(new Connection()));
            }
        }
        ~Comm(){
        }
        void AddConnection(std::shared_ptr<Connection> client);
        bool StartClient(sf::Uint16 port, sf::IpAddress addr);
        bool StartServer(sf::Uint16 port);
        void Stop();
        void Send(CommEvent &p);
        bool Receive(CommEvent &p);

        /*std::vector<sf::Uint32> getConnectionIds();*/
    protected:
        sf::IpAddress address;
        sf::Uint16 port;
        sf::TcpListener Listener;

        static void LooperClientHandler(std::shared_ptr<LooperClientHandlerArg> arg);
		std::vector<std::shared_ptr<sf::Thread> > looperClientHandlerThreads;

        static void LooperListener(std::shared_ptr<LooperListenerArg> arg);
		std::shared_ptr<sf::Thread> looperListenerThread;

        static void LooperMaster(Comm* comm);
        sf::Thread LooperMasterThread;

        sf::SocketSelector ListeningSelector;
        sf::SocketSelector ConnectingSelector;
        sf::SocketSelector EstablishedSelector;

        sf::Mutex ListeningMutex;
        sf::Mutex ConnectingMutex;
        sf::Mutex EstablishedMutex;
        sf::Mutex SystemMutex;

        std::vector<std::shared_ptr<Connection> > Listening;
        std::vector<std::shared_ptr<Connection> > Connecting;
        std::vector<std::shared_ptr<Connection> > Established;

        std::vector<std::shared_ptr<Connection> > connections;

        std::queue<sf::Packet> SystemPackets;

        bool NotDone;
        sf::Uint32 TotalConnectCount;

        //SendSystem enqueues a CommEvent into the incoming queues - where the client of this class will
        // then be able to processes them along other subsystem events(sfml-window)
        void SendSystem(CommEventType::CET cet, sf::Uint32 connectionId, std::string msg);
    };
}

#endif


