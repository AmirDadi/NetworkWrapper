#ifndef DADI_CLIENT
#define DADI_CLIENT

#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent
#include <string>
#include "Socket.h"
#include <thread>


class Client{
public:
	Client(int server_port);
	std::string receive_data();
	bool send_data(std::string msg);
	std::string send_message(std::string); //return response from server
	//virtual void get_input() = 0;
	//virtual void run();
	~Client();
private:
	bool connect(std::string, int);
	
	int sock;
    std::string address;
    int port;
    struct sockaddr_in server;
    std::thread* input_thread;
};

#endif