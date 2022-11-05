#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{

    // PART 1 - Create a socket
    // socket - creates an endpoint for communication and returns a file descriptor
    //      that refers to that endpoint.
    // file descriptor - An interger. The Unix abstraction for an open input/output stream:
    //      a file, a network connection, a pipe (a communication channel between
    //      processes), a terminal, etc.
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket!";
        return -1;
    }
    // PART 2 - Bind the socket to a IP / port
    // declare a socket descitpor to hold generic info the process needs
    // like IP version, port number, x. This is used with the bind function
    // to name the socket
    sockaddr_in hint;
    // tell computer we want to use IPv4
    hint.sin_family = AF_INET;
    // htons - need to use the little edian algorithim to store this
    // port number 54000 because this is an intel chip.
    hint.sin_port = htons(54000);
    // inet_pton - converts an address like 127.0.0.1 from text to binary form
    //      returns  1  on success (network address was successfully converted).
    //      0 is returned if src does not contain a character string representing a
    //      valid network address in the specified address family.  If af does not
    //      contain a valid address family, -1  is  returned  and errno is set to EAFNOSUPPORT.
    // arg 1 - specify it you want address structure IPv4 or IPv6
    // arg 2 - can be any IP address - giving it 0.0.0.0 says give me any valid IP address
    // arg 3 - uses arg 2 to write to a buffer with the proper address structure
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    // Traditionally, this operation bind, is called “assigning a name to a socket”.
    if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
    {
        cerr << "Can't bind to IP/Port";
        return -2;
    }

    // PART 3 -  Mark the socket for listening in
    // SOMAXCONN - max number of connections allowed
    if (listen(listening, SOMAXCONN) == -1)
    {
        cerr << "Can't listen!";
        return -3;
    }

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
        cerr << "Problem with client connecting";
        return -4;
    }

    // PART 5 -  Close the listening socket
    close(listening);

    // need to clean things up with memset so that we don't get unexpected behavior

    // ptr ==> Starting address of memory to be filled
    // x   ==> Value to be filled
    // n   ==> Number of bytes to be filled starting
    //         from ptr to be filled
    // void *memset(void *ptr, int x, size_t n);
    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    // function getnameinfo is the inverse of getaddrinfo(3): it
    //    converts a socket address to a corresponding host and service
    // On success, 0 is returned, and node and service names, if
    // requested, are filled with null-terminated strings, possibly
    // truncated to fit the specified buffer lengths
    int result = getnameinfo((sockaddr *)&client,
                             sizeof(client),
                             host,
                             NI_MAXHOST,
                             svc,
                             NI_MAXSERV,
                             0);
    // got host name info successfully
    if (result)
    {
        cout << host << " connected on " << svc << endl;
    }
    // there was an issue so do some things manually
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << "connected on" << ntohs(client.sin_port) << endl;
    }

    // PART 6 -  While receiving - display messge, echo message
    char buf[4096];

    while (true)
    {
        // Clear the buffer
        memset(buf, 0, 4096);
        // Wait for a message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if (bytesRecv == -1)
        {
            cerr << "There was a connection issue" << endl;
            break;
        }

        if (bytesRecv == 0)
        {
            cout << "The client disconnected" << endl;
            break;
        }

        // Display Message
        cout << "Recieved: " << string(buf, 0, bytesRecv) << endl;

        // Resend message
        send(clientSocket, buf, bytesRecv + 1, 0);
    }

    // PART 7 -  Close socket
    close(clientSocket);

    return 0;
}