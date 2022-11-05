// #pragma once

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

// Forward declaration of class
class CTcpListener;

// Callback to data recieved
typedef void (*MessageRecievedHandler)(CTcpListener *listen, int socketId, std::string msg);

class CTcpListener
{
public:
    CTcpListener(std::string ipAddress, int port, MessageRecievedHandler handler);

    ~CTcpListener();

    // Send a message to a specified client
    void Send(int clientSocket, std::string msg);

    // Initialize socket
    bool Init();

    // The main processsing loop
    void Run(int listening);

    void Cleanup();

    // Send back messge
    // Recieve Loop
    // Cleanup

private:
    // Create a socket
    int CreateSocket();

    // Wait for connection
    // socket WaitForConnection();
    int WaitForConnection(int listening);

    std::string m_ipAddress;
    int m_port;
    MessageRecievedHandler MessageReceived;
};