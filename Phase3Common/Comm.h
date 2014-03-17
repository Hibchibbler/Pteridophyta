
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

    typedef std::shared_ptr<sf::Packet> SPacket;

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
            isConnected = false;
            error = false;

            /*Socket = NULL;
            SendMutex = NULL;
            RecvMutex = NULL;*/
        }

        bool isConnected;
        bool error;
        sf::TcpSocket Socket;
        sf::Uint32 connectionId;
        std::queue<SPacket> recvQueue;
        std::queue<SPacket> sendQueue;
        sf::Mutex sendMutex;
        sf::Mutex recvMutex;
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
        SPacket packet;
        sf::Uint32 connectionId;
    private:
    };


    class Comm
    {
    public:
        Comm();
        ~Comm();
        //void AddConnection(std::shared_ptr<Connection> client);
        bool startClient(sf::Uint16 port, sf::IpAddress addr);
        bool startServer(sf::Uint16 port);
        void stop();
        void send(CommEvent &p);
        bool receive(CommEvent &p);

        static void initializeCommEvent (CommEvent & ce, sf::Uint32 cid);
    protected:
        sf::IpAddress                               address;
        sf::Uint16                                  port;
        sf::TcpListener                             listener;

        static void LooperClientHandler(std::shared_ptr<LooperClientHandlerArg> arg);
		std::vector<std::shared_ptr<sf::Thread> >   looperClientHandlerThreads;

        static void LooperListener(std::shared_ptr<LooperListenerArg> arg);
		std::shared_ptr<sf::Thread>                 looperListenerThread;

        sf::SocketSelector                          listenerSelector;

        //
        //connectionMutex synchronizes acces to connections vector.
        //Used by Receive and Send
        //
        sf::Mutex                                   connectionsMutex;
        sf::Mutex                                   SystemMutex;

        std::vector<std::shared_ptr<Connection> >   connections;
        std::queue<CommEvent>                       SystemPackets;

        bool                                        NotDone;
        sf::Uint32                                  TotalConnectCount;

        //sendSystem enqueues a CommEvent into the incoming queues - where the client of this class will
        // then be able to processes them along other subsystem events(sfml-window)
        void sendSystem(CommEventType::CET cet, sf::Uint32 connectionId, std::string msg);

    };
}

#endif


