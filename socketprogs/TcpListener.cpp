// #pragma once

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "TcpListener.h"

#define MAX_BUFFER_SIZE (8192)


// // Callback to data recieved
// typedef void (*MessageRecievedHandler)(CTcpListener listen, int socketId, std::string msg);

// class CTcpListener
// {
// public:

CTcpListener::CTcpListener(std::string ipAddress, int port, MessageRecievedHandler handler)
    : m_ipAddress(ipAddress), m_port(port), MessageReceived(handler){

                                            };

CTcpListener::~CTcpListener()
{
    Cleanup();
};

// Send a message to a specified client
void CTcpListener::Send(int clientSocket, std::string msg)
{
    send(clientSocket, msg.c_str(), msg.size() + 1, 0);
};

// Initialize socket
bool CTcpListener::Init(){
    // 12 mins - this seems to be only things windows needs
    return false;

};

// The main processsing loop
void CTcpListener::Run()
{
    // int clientSocket = WaitForConnection(listening);

    // PART 6 -  While receiving - display messge, echo message
    char buf[MAX_BUFFER_SIZE];
    int bytesRecv = 0;

    do {
        // Clear the buffer
        memset(buf, 0, sizeof(buf));
        int listening = CreateSocket();

        if (listening < 0){
            std::cerr << "There was an issue with the listening socket." << std::endl;
            break;
        }


        int clientSocket = WaitForConnection(listening);




        // Wait for a message
        bytesRecv = recv(clientSocket, buf, MAX_BUFFER_SIZE, 0);
        if (bytesRecv == -1)
        {
            std::cerr << "There was a connection issue" << std::endl;
            break;
        }

        if (bytesRecv == 0)
        {
            std::cout << "The client disconnected" << std::endl;
            break;
        }

        // Display Message
        std::cout << "Recieved: " << std::string(buf, 0, bytesRecv) << std::endl;

        if (bytesRecv > 0 && MessageReceived != NULL)
        {
            MessageReceived(this, clientSocket, std::string(buf, 0, bytesRecv));
        }

        // Resend message
        send(clientSocket, buf, bytesRecv + 1, 0);
    }    while (bytesRecv > 0);

    // PART 7 -  Close socket
    // close(clientSocket);
};

// Send back messge
// Recieve Loop
// Cleanup
void CTcpListener::Cleanup(){
    // PART 5 -  Close the listening socket
    // close(listening);
    // need to clean things up with memset so that we don't get unexpected behavior
    // memset(host, 0, NI_MAXHOST);
    // memset(svc, 0, NI_MAXSERV);
};

// Create a socket
int CTcpListener::CreateSocket()
{
    // PART 1 - Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "Can't create a socket!";
        return -1;
    }
    // PART 2 - Bind the socket to a IP / port
    sockaddr_in hint;
    // tell computer we want to use IPv4
    hint.sin_family = AF_INET;
    // htons - need to use the little edian algorithim to store this
    // port number 54000 because this is an intel chip.
    hint.sin_port = htons(54000);
    // inet_pton - converts an address like 127.0.0.1 from text to binary form
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    // Traditionally, this operation bind, is called “assigning a name to a socket”.
    if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
    {
        std::cerr << "Can't bind to IP/Port";
        return -2;
    }
    // PART 3 -  Mark the socket for listening in
    // SOMAXCONN - max number of connections allowed
    if (listen(listening, SOMAXCONN) == -1)
    {
        std::cerr << "Can't listen!";
        return -3;
    }

    // socket is successfully listening
    return listening;
};

// Wait for connection
// socket WaitForConnection();
// need to pass in the listening socket from above
int CTcpListener::WaitForConnection(int listening)
{

    // not interested in finding anything out about the client.
    // just want to see if it connects
    // int client = accept(listening, NULL, NULL);

    // PART 4 -  Accept a call
    // setup some things for the client's machine
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST]; //
    char svc[NI_MAXSERV];

    // accept the incoming connection
    int clientSocket = accept(listening,
                              (sockaddr *)&client,
                              &clientSize);
    if (clientSocket == -1)
    {
        std::cerr << "Problem with client connecting";
        return -4;
    }

    // PART 5 -  Close the listening socket
    close(listening);

    return clientSocket;
};
