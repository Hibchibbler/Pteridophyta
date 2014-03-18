/**********************************************************************************
Comm.cpp

Copyright 2013
Daniel Ferguson
**********************************************************************************/

#include "Comm.h"
#include <iostream>

#define SELECTOR_TIMEOUT            0.001f
#define COMM_THREAD_LOOP_DELAY      40000 //40 ms

namespace bali{

Comm::Comm()
{
    NotDone = true;
    TotalConnectCount=0;

}

Comm::~Comm()
{
}

bool Comm::startClient(sf::Uint16 port, sf::IpAddress addr)
{//We are creating a connecting client
    this->address = addr;
    this->port = port;


    NotDone = true;
    //AddConnection(std::shared_ptr<Connection>(new Connection()));
    std::cout << "StartClient" << std::endl;
    //Launch Client Handler Thread
    std::shared_ptr<Connection> newConn(new Connection);

    sf::Socket::Status s = newConn->Socket.connect(address, port);//"192.168.2.110"
    if (s == sf::Socket::Done){

        newConn->connectionId = TotalConnectCount;
        newConn->isConnected = true;
        newConn->selector.add(newConn->Socket);

        connectionsMutex.lock();
        connections.push_back(newConn);
        connectionsMutex.unlock();

        sendSystem(CommEventType::Connected, TotalConnectCount, std::string("Outgoing Connection Request was accepted."));
        TotalConnectCount++;

        std::shared_ptr<sf::Thread>
                    thread(
                        std::make_shared<sf::Thread>(
                                Comm::LooperClientHandler,
                                std::make_shared<LooperClientHandlerArg>(this, newConn)
                        )
                    );
        thread->launch();
        looperClientHandlerThreads.push_back(thread);




    }else {
        if(s == sf::Socket::Disconnected)
            sendSystem(CommEventType::Disconnect, TotalConnectCount, std::string("Failed to Connect to Remote Host"));
        else
            sendSystem(CommEventType::Error,  TotalConnectCount, std::string("Error on connect"));
        return false;
    }
    return true;
}

//TODO: StartServer operates on the Established connections container
bool Comm::startServer(sf::Uint16 port)
{//We are creating a listener
    TotalConnectCount = 0;
    NotDone = true;
    listener.listen(port);

    std::cout << "StartServer" << std::endl;

    //Launch Listener Thread
    looperListenerThread = std::shared_ptr<sf::Thread>
                (
                    std::make_shared<sf::Thread>(
                            Comm::LooperListener,
                            std::make_shared<LooperListenerArg>(this)
                    )
                );
    looperListenerThread->launch();
    return true;
}

void Comm::stop()
{
    NotDone = false;
    std::cout << "waiting for Looper Thread to stop" << std::endl;

    //
    //TODO:thread joins
    //

    listener.close();

    connections.clear();
}

 //Send operates on the connections container
void Comm::send(CommEvent &gpacket)
{
    connectionsMutex.lock();
    std::vector<std::shared_ptr<Connection> >::iterator i = connections.begin();
    for (;i != connections.end();i++){
        std::shared_ptr<Connection> c = (*i);

        if (gpacket.connectionId == -1 || gpacket.connectionId == c->connectionId){
            c->sendMutex.lock();
            c->sendQueue.push(gpacket.packet);
            c->sendMutex.unlock();
        }
    }
    connectionsMutex.unlock();
}

//Receive operates on the connections container
bool Comm::receive(CommEvent &gpacket)
{
    //first check for system messages
    SystemMutex.lock();
    if(!SystemPackets.empty())
    {
        gpacket = SystemPackets.front();
        SystemPackets.pop();
        SystemMutex.unlock();
        return true;
    }
    SystemMutex.unlock();


    //now check for data
    connectionsMutex.lock();
    std::vector<std::shared_ptr<Connection> >::iterator i = connections.begin();
    for (;i != connections.end();i++)
    {
        std::shared_ptr<Connection> c = (*i);
        if (!c->error)
        {
            c->recvMutex.lock();
            if (!c->recvQueue.empty())
            {
                gpacket.packet = c->recvQueue.front();
                gpacket.connectionId = c->connectionId;
                c->recvQueue.pop();
                c->recvMutex.unlock();
                connectionsMutex.unlock();
                return true;
            }
        }
        c->recvMutex.unlock();
    }
    connectionsMutex.unlock();
    return false;
}


void Comm::sendSystem(CommEventType::CET cet, uint32_t connectionId, std::string msg)
{
    //sf::Packet packet;
    CommEvent evt;
    Comm::initializeCommEvent(evt, connectionId);

    *evt.packet << cet << msg;
    SystemMutex.lock();
    SystemPackets.push(evt);
    SystemMutex.unlock();
}

void Comm::initializeCommEvent(CommEvent & ce, uint32_t cid)
{
    ce.connectionId = cid;
    ce.packet = std::shared_ptr<sf::Packet>(new sf::Packet());
}

//
//CommListenLooper handles all incoming connection requests
//and hands them off to a thread that is dedicated to the connection
//
void Comm::LooperListener(std::shared_ptr<LooperListenerArg> arg)
{
    std::cout << "LooperListener here" << std::endl;
	Comm* comm = arg->comm;

	comm->listenerSelector.add(comm->listener);

    while (comm->NotDone)
    {
        if (comm->listenerSelector.wait(sf::milliseconds(100)))
        {
            std::shared_ptr<Connection> newConn(new Connection());

            sf::Socket::Status s = comm->listener.accept(newConn->Socket);
            if (s == sf::Socket::Done){
                std::cout << "Client connected from " << newConn->Socket.getRemoteAddress().toString() << std::endl;

                //newConn->Socket.setBlocking(false);
                newConn->connectionId = comm->TotalConnectCount;
                newConn->isConnected = true;
                newConn->selector.add(newConn->Socket);

                comm->connectionsMutex.lock();
                comm->connections.push_back(newConn);
                comm->connectionsMutex.unlock();

                comm->sendSystem(CommEventType::Connected, comm->TotalConnectCount, std::string("accepted Connection Request"));
                comm->TotalConnectCount++;
                //
                //Initialize a new client thread.
                //The thread is owned by a shared_ptr. we keep a local temp copy .
                //The threads' constructor(that is used here) takes two parameters:
                //1) a function pointer (static member/free)
                //2) a struct of arguments.
                //  2.A) the struct is owned by a shared_ptr. we do not store a local temp copy.
                //
                std::shared_ptr<sf::Thread>
                    thread(
                        std::make_shared<sf::Thread>(
                                Comm::LooperClientHandler,
                                std::make_shared<LooperClientHandlerArg>(comm, newConn)
                        )
                    );

                comm->looperClientHandlerThreads.push_back(thread);
                thread->launch();
            }else{
                //TODO: Handle This!!!!!!!!!
                std::cout << "Unable to accept" << std::endl;
            }
        }
    }
}

void Comm::LooperClientHandler(std::shared_ptr<LooperClientHandlerArg> arg)
{
    std::cout << "LooperClientHandler here" << std::endl;
	Comm* comm = arg->comm;
	std::shared_ptr<Connection> conn = arg->conn;


	while (conn->isConnected && comm->NotDone)
	{
        //Send any pending outgoing data

        //The assumption is, that once the size is captured
        //the size will only increase, and so we will send the
        //number of packets we knew of at this point in time.
        conn->sendMutex.lock();
        int sz = conn->sendQueue.size();
        conn->sendMutex.unlock();

        while(sz > 0)
        {
            std::cout << "Sending" << std::endl;

            conn->sendMutex.lock();
            SPacket packet = conn->sendQueue.front();
            conn->sendQueue.pop();
            conn->sendMutex.unlock();

            sf::Socket::Status s = conn->Socket.send(*packet);
            if (s == sf::Socket::Done)
            {
                //comm->sendSystem(CommEventType::Sent, conn->connectionId, std::string("Sent"));
            }else if (s == sf::Socket::NotReady)
            {
                std::cout << "Not Ready To Send." << std::endl;
            }else if (s == sf::Socket::Disconnected)
            {
                comm->sendSystem(CommEventType::Disconnect, conn->connectionId, std::string("Client disconnected"));
                conn->isConnected = false;
                break;
            }
            else
            {
                comm->sendSystem(CommEventType::Error, conn->connectionId, std::string("Error on Send"));
                conn->error = true;
                conn->isConnected = false;
                break;
            }
            sz--;
        }

        if (conn->selector.wait(sf::microseconds(1)))
        {
            std::cout << "Receiving" << std::endl;
            CommEvent RecvPacket;
            Comm::initializeCommEvent(RecvPacket, conn->connectionId);

            sf::Socket::Status s;
            s = conn->Socket.receive(*RecvPacket.packet);
            if (s == sf::Socket::Done){
                conn->recvMutex.lock();
                conn->recvQueue.push(RecvPacket.packet);
                conn->recvMutex.unlock();
            }
            else if (s == sf::Socket::NotReady){
                //std::cout << "Partial Receive?" << std::endl;
            }else if (s == sf::Socket::Status::Error){
                comm->sendSystem(CommEventType::Error, RecvPacket.connectionId, std::string("Error on receive"));
                conn->error = true;
                conn->isConnected = false;
            }else if(s == sf::Socket::Disconnected){
                comm->sendSystem(CommEventType::Disconnect, RecvPacket.connectionId, std::string("Client disconnected"));
                conn->isConnected = false;
            }
        }

        sf::sleep(sf::milliseconds(20));
	}
}


}//end namespace bali
