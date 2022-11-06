.PHONY=clean

#Compiler
CC = g++
#Compiler Flags
CFLAGS = -o



sock: sockprog_server.cpp
	$(CC) $(CFLAGS) sockprog_server sockprog_server.cpp

tcplisten: TcpListener.cpp
	g++ -o TcpListener TcpListener.cpp

all: TcpListener.cpp main.cpp
	g++ -o TcpListener TcpListener.cpp
	g++ -o main main.cpp 

clean:

	rm -rf sockprog_server TcpListener main