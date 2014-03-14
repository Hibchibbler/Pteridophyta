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

bool Comm::StartClient(sf::Uint16 port, sf::IpAddress addr)
{//We are creating a connecting client
    this->address = addr;
    this->port = port;

    TotalConnectCount = 0;
    NotDone = true;
    AddConnection(std::shared_ptr<Connection>(new Connection()));
    std::cout << "StartClient" << std::endl;
    LooperMasterThread.launch();
    return true;
}

//TODO: StartServer operates on the Established connections container
bool Comm::StartServer(sf::Uint16 port)
{//We are creating a listener
    TotalConnectCount = 0;
    NotDone = true;
    Listener.listen(port);
    ListeningSelector.add(Listener);
    std::cout << "StartServer" << std::endl;
    //LooperMasterThread.launch();
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

void Comm::Stop()
{
    NotDone = false;
    std::cout << "waiting for Looper Thread to stop" << std::endl;
    LooperMasterThread.wait();

    Listener.close();
    Connecting.clear();
    Established.clear();
}

 //Send operates on the Established connections container
void Comm::Send(CommEvent &gpacket)
{
    //EstablishedMutex.lock();
    std::vector<std::shared_ptr<Connection> >::iterator i = Established.begin();
    for (;i != Established.end();i++){
        if (!(*i)->IsConnected)
            continue;
        if (gpacket.connectionId == -1 || gpacket.connectionId == (*i)->connectionId){
            (*i)->SendMutex.lock();
            (*i)->SendQueue.push(gpacket.packet);
            (*i)->SendMutex.unlock();
        }
    }
    //EstablishedMutex.unlock();
}

//Receive operates on the Established connections container
bool Comm::Receive(CommEvent &gpacket)
{
    //first check for system messages
    SystemMutex.lock();
    if(!SystemPackets.empty()){
        gpacket.packet = SystemPackets.front();
        SystemPackets.pop();
        SystemMutex.unlock();
        gpacket.connectionId = -1;
        return true;
    }
    SystemMutex.unlock();


    //now check for data
    //EstablishedMutex.lock();
    std::vector<std::shared_ptr<Connection> >::iterator i = Established.begin();
    for (;i != Established.end();i++){
        if ((*i)->IsConnected && !(*i)->error)
        {
            (*i)->RecvMutex.lock();
            if (!(*i)->RecvQueue.empty()){
                gpacket.packet = (*i)->RecvQueue.front();
                gpacket.connectionId = (*i)->connectionId;
                (*i)->RecvQueue.pop();
                (*i)->RecvMutex.unlock();
                //EstablishedMutex.unlock();
                return true;
            }
        }
        (*i)->RecvMutex.unlock();
    }
    //EstablishedMutex.unlock();
    return false;
}

//AddConnection adds to the Connecting connections container
void Comm::AddConnection(std::shared_ptr<Connection> client)
{
    ConnectingMutex.lock();
    Connecting.push_back(client);
    ConnectingMutex.unlock();
}

void Comm::SendSystem(CommEventType::CET cet, sf::Uint32 connectionId, std::string msg)
{
    sf::Packet packet;
    packet << cet << connectionId << msg;
    SystemMutex.lock();
    SystemPackets.push(packet);
    SystemMutex.unlock();
}

//
//CommListenLooper handles all incoming connection requests
//and hands them off to a thread that is dedicated to the connection
//
void Comm::LooperListener(std::shared_ptr<LooperListenerArg> arg)
{
    std::cout << "LooperListener here" << std::endl;
	Comm* comm = arg->comm;
    while (comm->NotDone){
        std::shared_ptr<Connection> newConn(new Connection());

        sf::Socket::Status s = comm->Listener.accept(newConn->Socket);
        if (s == sf::Socket::Done){
            std::cout << "Client connected from " << newConn->Socket.getRemoteAddress().toString() << std::endl;

			//newConn->Socket.setBlocking(false);
            newConn->connectionId = comm->TotalConnectCount;
            newConn->IsConnected = true;
            newConn->selector.add(newConn->Socket);

            comm->EstablishedMutex.lock();
            comm->Established.push_back(newConn);
            comm->EstablishedMutex.unlock();

            comm->SendSystem(CommEventType::Connected, comm->TotalConnectCount, std::string("accepted Connection Request"));
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
            thread->launch();
			comm->looperClientHandlerThreads.push_back(thread);

        }else{
            //TODO: Handle This!!!!!!!!!
            std::cout << "Unable to accept" << std::endl;
        }
        sf::sleep(sf::milliseconds(10));
    }
}

void Comm::LooperClientHandler(std::shared_ptr<LooperClientHandlerArg> arg)
{
    std::cout << "LooperClientHandler here" << std::endl;
	Comm* comm = arg->comm;
	std::shared_ptr<Connection> conn = arg->conn;

	while (comm->NotDone){
        //Send any pending outgoing data
        while(!conn->SendQueue.empty()){
            std::cout << "Sending" << std::endl;
            //std::cout << conn->SendQueue.size() << std::endl;
            sf::Packet packet = conn->SendQueue.front();
            conn->SendQueue.pop();
            sf::Socket::Status s = conn->Socket.send(packet);
            if (s == sf::Socket::Done){
                //comm->SendSystem(CommEventType::Sent, conn->connectionId, std::string("Sent"));
            }else if (s == sf::Socket::NotReady)
            {
                std::cout << "Not Ready To Send." << std::endl;
            }else{
                if (s == sf::Socket::Disconnected)
                    comm->SendSystem(CommEventType::Disconnect, conn->connectionId, std::string("Client disconnected"));
                else
                    comm->SendSystem(CommEventType::Error, conn->connectionId, std::string("Error on Send"));
                conn->error = true;

                break;
            }
        }

        if (conn->selector.wait(sf::microseconds(1)))
        {
            std::cout << "Receiving" << std::endl;
            CommEvent RecvPacket;
            RecvPacket.connectionId = conn->connectionId;
            sf::Socket::Status s;
            s = conn->Socket.receive(RecvPacket.packet);
            if (s == sf::Socket::Done){
                conn->RecvMutex.lock();
                conn->RecvQueue.push(RecvPacket.packet);
                conn->RecvMutex.unlock();

            }
            else if (s == sf::Socket::NotReady){
                //std::cout << "Partial Receive? Not pushing packet onto rx queue." << std::endl;
            }
            else if (s == sf::Socket::Status::Error){
                comm->SendSystem(CommEventType::Error, RecvPacket.connectionId, std::string("Error on receive"));
                conn->error = true;
            }else if(s == sf::Socket::Disconnected){
                comm->SendSystem(CommEventType::Disconnect, RecvPacket.connectionId, std::string("Client disconnected"));
            }
        }

        sf::sleep(sf::milliseconds(10));
	}
}

void LooperClientHandlerContext::LooperClientHandler()
{
    std::cout << "LooperClientHandlerContext::LooperClientHandler here" << std::endl;

	while (comm->NotDone){
        //Send any pending outgoing data
        while(!conn->SendQueue.empty()){
            std::cout << "Sending" << std::endl;
            //std::cout << conn->SendQueue.size() << std::endl;
            sf::Packet packet = conn->SendQueue.front();
            conn->SendQueue.pop();
            sf::Socket::Status s = conn->Socket.send(packet);
            if (s == sf::Socket::Done){
                //comm->SendSystem(CommEventType::Sent, conn->connectionId, std::string("Sent"));
            }else if (s == sf::Socket::NotReady)
            {
                std::cout << "Not Ready To Send." << std::endl;
            }else{
                if (s == sf::Socket::Disconnected)
                    comm->SendSystem(CommEventType::Disconnect, conn->connectionId, std::string("Client disconnected"));
                else
                    comm->SendSystem(CommEventType::Error, conn->connectionId, std::string("Error on Send"));
                conn->error = true;

                break;
            }
        }

        if (conn->selector.wait(sf::microseconds(1)))
        {
            std::cout << "Receiving" << std::endl;
            CommEvent RecvPacket;
            RecvPacket.connectionId = conn->connectionId;
            sf::Socket::Status s;
            s = conn->Socket.receive(RecvPacket.packet);
            if (s == sf::Socket::Done){
                conn->RecvMutex.lock();
                conn->RecvQueue.push(RecvPacket.packet);
                conn->RecvMutex.unlock();

            }
            else if (s == sf::Socket::NotReady){
                //std::cout << "Partial Receive? Not pushing packet onto rx queue." << std::endl;
            }
            else if (s == sf::Socket::Status::Error){
                comm->SendSystem(CommEventType::Error, RecvPacket.connectionId, std::string("Error on receive"));
                conn->error = true;
            }else if(s == sf::Socket::Disconnected){
                comm->SendSystem(CommEventType::Disconnect, RecvPacket.connectionId, std::string("Client disconnected"));
            }
        }

        sf::sleep(sf::milliseconds(10));
	}
}

void Comm::LooperMaster(Comm* comm)
{
    std::cout << "Looper" << std::endl;

    while (comm->NotDone){
        std::vector<std::shared_ptr<Connection> >::iterator i;
        // Check for, and process, any new connection requests
        //TODO: spawn a thread for each willing listener;
        //      the listener mutex and selector stuff is WIP.
        //
        if (comm->ListeningSelector.wait(sf::microseconds(1))){

            int newConnIndex = 0;
            for (newConnIndex = 0 ; newConnIndex < 15;newConnIndex++)
            {
                if (!comm->Established[newConnIndex]->IsConnected)
                    break;
            }

            sf::Socket::Status s= comm->Listener.accept(comm->Established[newConnIndex]->Socket);
            if (s == sf::Socket::Done){
                std::cout << "Client connected from " << comm->Established[newConnIndex]->Socket.getRemoteAddress().toString() << std::endl;

                // Add the client to our internal list, and add the client to the selector
                comm->Established[newConnIndex]->connectionId = comm->TotalConnectCount;
                comm->Established[newConnIndex]->IsConnected = true;
                comm->EstablishedSelector.add(comm->Established[newConnIndex]->Socket);
                comm->SendSystem(CommEventType::Connected, comm->TotalConnectCount, std::string("accepted Connection Request"));
                comm->TotalConnectCount++;
            }else{
                //TODO: Handle This!!!!!!!!!
                std::cout << "Unable to accept" << std::endl;
            }
        }

        //Check for and process and new outgoing connections
        comm->ConnectingMutex.lock();
        i = comm->Connecting.begin();
        while (i != comm->Connecting.end()){
            sf::Socket::Status s = (*i)->Socket.connect(comm->address, comm->port);//"192.168.2.110"
            if (s == sf::Socket::Done){

                (*i)->connectionId = comm->TotalConnectCount;
                (*i)->IsConnected = true;

                for (int y = 0 ; y < 15;y++)
                {
                    if (!comm->Established[y]->IsConnected)
                    {
                        comm->Established[y] = (*i);
                        break;
                    }
                }
                comm->EstablishedSelector.add((*i)->Socket);
                comm->SendSystem(CommEventType::Connected,comm->TotalConnectCount, std::string("Connected"));
                comm->TotalConnectCount++;
                //The last thing we do.
                i = comm->Connecting.erase(i);
            }else {
                if(s == sf::Socket::Disconnected)
                    comm->SendSystem(CommEventType::Disconnect, comm->TotalConnectCount, std::string("Failed to Connect to Remote Host"));
                else
                    comm->SendSystem(CommEventType::Error,  comm->TotalConnectCount, std::string("Error on connect"));
                //we'd better remove the socket from the selector
                i = comm->Connecting.erase(i);
            }
        }
        comm->ConnectingMutex.unlock();

        //Retrieve new incoming data
        if ( comm->EstablishedSelector.wait(sf::microseconds(1)) ) {
            //Some data is available
            i = comm->Established.begin();
            for (;i != comm->Established.end();i++){
                if (!(*i)->IsConnected || (*i)->error)
                    continue;
                if (comm->EstablishedSelector.isReady((*i)->Socket)){
                    //Client Ready to receive

                    CommEvent RecvPacket;
                    RecvPacket.connectionId = (*i)->connectionId;
                    sf::Socket::Status s;
                    s = (*i)->Socket.receive(RecvPacket.packet);
                    if (s == sf::Socket::Done){

                        (*i)->RecvMutex.lock();
                        (*i)->RecvQueue.push(RecvPacket.packet);
                        (*i)->RecvMutex.unlock();

                    }else{

                        if(s == sf::Socket::Disconnected)
                            comm->SendSystem(CommEventType::Disconnect, RecvPacket.connectionId, std::string("Client disconnected"));
                        else
                            comm->SendSystem(CommEventType::Error, RecvPacket.connectionId, std::string("Error on receive"));
                        (*i)->error = true;
                        //we'd better remove the socket from the selector
                        comm->EstablishedSelector.remove((*i)->Socket);
                    }
                }
            }
        }

        //Send any pending outgoing data
        i =  comm->Established.begin();
        for (;i != comm->Established.end();i++){
            if (!(*i)->IsConnected || (*i)->error)
                continue;
            (*i)->SendMutex.lock();
            while(!(*i)->SendQueue.empty()){
                //std::cout << (*i)->SendQueue.size() << std::endl;
                sf::Packet packet = (*i)->SendQueue.front();
                (*i)->SendQueue.pop();
                sf::Socket::Status s = (*i)->Socket.send(packet);
                if (s == sf::Socket::Done){
                    //comm->SendSystem(CommEventType::Sent, (*i)->connectionId, std::string("Sent"));
                }else{
                    if (s == sf::Socket::Disconnected)
                        comm->SendSystem(CommEventType::Disconnect, (*i)->connectionId, std::string("Client disconnected"));
                    else
                        comm->SendSystem(CommEventType::Error, (*i)->connectionId, std::string("Error on Send"));
                    (*i)->error = true;
                    //we'd better remove the socket from the selector
                    comm->EstablishedSelector.remove((*i)->Socket);
                    break;
                }
            }
            (*i)->SendMutex.unlock();
        }
        //Sleep little baby
        sf::sleep(sf::milliseconds(0));
    }
}





}//end namespace bali
