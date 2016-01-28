#include "Socket.h"
#include <iostream>
using namespace std;

Socket::Socket(int multiple_connection){
    int socket_fd;
    if( (fd = socket(AF_INET , SOCK_STREAM , 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    allow_multiple_connection(multiple_connection);
}

void Socket::allow_multiple_connection(int opt){
    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}


void Socket::bind(int port){
    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );
      
    if (::bind(fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", port);
}

void Socket::listen(int queue, int max_number_of_clients){
	if (::listen(fd, queue) < 0){
		perror("listen");
		exit(EXIT_FAILURE);
	}
	for(int i=0; i<max_number_of_clients; i++)
		clients_socket.push_back(0);
}
Message Socket::select(){
	FD_ZERO(&fds);
	//add master socket to set
	FD_SET(fd, &fds);
	int max_sd = fd;
	int max_clients = clients_socket.size(); 
	//add child sockets to set
	for (int i = 0 ; i < max_clients ; i++){
		//socket descriptor
		int sd = clients_socket[i];
		 
		//if valid socket descriptor then add to read list
		if(sd > 0)
			FD_SET( sd , &fds);
		 
		//highest file descriptor number, need it for the select function
		if(sd > max_sd)
			max_sd = sd;
	}
	//wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
	int activity = ::select( max_sd + 1 , &fds , NULL , NULL , NULL);
	
	if ((activity < 0) && (errno!=EINTR)) {
		printf("select error");
	}
	int new_socket;
	int addrlen = sizeof(address);
	if (FD_ISSET(fd, &fds)){ 
		if ((new_socket = accept(fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
			perror("accept");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < max_clients; i++){
			//if position is empty
			if( clients_socket[i] == 0 )
			{
				clients_socket[i] = new_socket;
				break;
			}
		}
		return Message(new_socket, NEW_CONNECTION);
	}
	else 
		return Message(0, NEW_MESSAGE);
}

string Socket::read(int sd){
	char buffer[MAX_BUFFER_SIZE];
	int res = ::read(sd, buffer, MAX_BUFFER_SIZE);
	//if res==0 throw disconnect exception
	buffer[res] = '\0';
	return string(buffer);
}

int Socket::send(int sd, string message){
	return ::send(sd, message.c_str(), message.size(), 0);	
}
