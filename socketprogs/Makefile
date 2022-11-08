.PHONY=clean

#Compiler
CC = g++
#Compiler Flags
CFLAGS = -wall -o



sock: sockprog_server.cpp
	$(CC) $(CFLAGS) sockprog_server sockprog_server.cpp

tcplisten: TcpListener.cpp
	$(CC) $(CFLAGS) TcpListener TcpListener.cpp

all: TcpListener.cpp main.cpp
	$(CC) $(CFLAGS) TcpListener TcpListener.cpp
	$(CC) $(CFLAGS) main main.cpp 

clean:

	rm -rf sockprog_server TcpListener main