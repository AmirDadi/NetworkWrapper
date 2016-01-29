#include <iostream>
#include "Socket.h"

using namespace std;

int main(){
	Socket server;
	server.bind(8888);
	server.listen(3);
	Message *msg;
	while(true){
		try{
			msg = server.select();
		}catch(NetworkException e){
			cout << "selecting...  " << e.what() << endl;
		}
		if(msg->get_type() == NEW_CONNECTION){
			cout << "New Connection " << msg->get_sender() << endl;
			server.send(msg->get_sender(), "hello\n");
			cout << "Welcoming Message Send!" << endl;
		}
		else{
			for(int i=0; i<server.clients_size(); i++){
				int client_socket = server.get_client_socket(i);
				try{
					if(server.has_incoming_message_on(client_socket)){
						string read_data = server.read(client_socket);
						cout << "new data from: " <<  client_socket  << " " << read_data << endl;
						server.send(client_socket, read_data); //echo message
					}
				}
				catch(NetworkException e){
					cout <<  client_socket << " Disconnecting..." << endl;
					server.disconnect_client(i--);
				}
			}
		}
	}
}
