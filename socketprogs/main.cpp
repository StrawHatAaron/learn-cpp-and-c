#include <iostream>
#include <string>

#include "TcpListener.cpp"


void Listener_MessageRecieved(CTcpListener *listener, int client, std::string msg);

int main()
{

    CTcpListener server("127.0.0.1", 54010, Listener_MessageRecieved);

    // if (server.Init())
    // {
    server.Run();
    // }

    return 0;
};

void Listener_MessageReceived(CTcpListener *listener, int client, std::string msg)
{
    listener->Send(client, msg);
};
