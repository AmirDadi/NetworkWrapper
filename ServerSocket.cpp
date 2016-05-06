#include "ServerSocket.h"
#include <thread>
using namespace std;

ServerSocket::ServerSocket(int port) : Socket(){
	bind(port);
	listen(3);
	thread* input = new thread(&ServerSocket::get_input, this);
}


void ServerSocket::run(){
	Message * msg;
	while(true){
		msg = select();
		if(msg->get_type() == NEW_CONNECTION){
			string result = on_connect(msg->get_sender());
			send(msg->get_sender(), result);
		}
		else{
			for(int i=0; i<clients_size(); i++){
				int client_socket = get_client_socket(i);
				try{
					if(has_incoming_message_on(client_socket)){
						string read_data = read(client_socket);
						string result = on_new_message(client_socket, read_data);
						send(client_socket, result); //echo message
					}
				}
				catch(NetworkException e){
					on_disconnect(client_socket);
					disconnect_client(i--);
				}
			}
		}
	}
}
