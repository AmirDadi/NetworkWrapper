all: server client
server: ServerSocket.o Socket.o server_main.cpp
	g++ -std=c++11 server_main.cpp ServerSocket.o Socket.o -o server
client: Client.o client_main.cpp
	g++ -std=c++11 client_main.cpp Client.o
Client.o: Client.cpp
	g++ -std=c++11 -c Client.cpp
ServerSocket.o: ServerSocket.cpp 
 	g++ -std=c++11 -c ServerSocket.cpp 
Socket.o: Socket.cpp
	g++ -std=c++11 -c Socket.cpp

clean:
	rm *.o *.out