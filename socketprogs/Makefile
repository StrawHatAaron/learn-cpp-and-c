.PHONY=clean

sock: sockprog_server.cpp
	g++ -o sockprog_server sockprog_server.cpp

tcplisten: TcpListener.cpp
	g++ -o TcpListener TcpListener.cpp

main: TcpListener.cpp main.cpp
	g++ -o main main.cpp

clean:

	rm -rf sockprog_server TcpListener main