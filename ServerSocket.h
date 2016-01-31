#ifndef DADI_SERVERSOCKET
#define DADI_SERVERSOCKET

#include <iostream>
#include <string>
#include "Socket.h"
class ServerSocket : public Socket{
public:
	ServerSocket(int port);
	virtual std::string on_connect(int id) { std::cout << "New Connection with id: " << id << std::endl; return "Hello";}
	virtual std::string on_new_message(int id, std::string msg) { std::cout << "Message: " << msg << " recieved" << std::endl; return msg; }  
	virtual void on_disconnect(int id) { std::cout << "Connection #" << id << "Disconnected" << std::endl; }
	void run();
private:
};	

#endif
