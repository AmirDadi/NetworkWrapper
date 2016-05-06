#ifndef DADI_NETWORK_HEADER
#define DADI_NETWORK_HEADER

#include <stdio.h>
#include <string.h>   //strlen
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <string>
#include <vector>
#include <stdlib.h>

#include "NetworkExceptions.h"
#define NEW_CONNECTION 0
#define NEW_MESSAGE 1
#define MAX_BUFFER_SIZE 2048

class Message{
public:
	Message(int sender, int type) : sender_id(sender), type(type) {}
	int get_sender(){ return sender_id;}
	int get_type() { return type;}
private:
	int sender_id;
	int type;
};

class Socket{
public:
	Socket(int multiple_connection = 1);
	void bind(int port);
	void listen(int queue);
	Message* select();
	int send(int , std::string data);
	std::string read(int );
	int clients_size() { return clients_socket.size();} 
	int get_client_socket(int i) { return clients_socket[i]; }
	bool has_incoming_message_on(int sd) { return FD_ISSET(sd, &fds); } 
	void disconnect_client(int i); 
	~Socket();
private:
	void allow_multiple_connection(int opt=true);
	struct sockaddr_in address;
	int fd;
	std::vector<int> clients_socket;
	fd_set fds;
};
#endif
