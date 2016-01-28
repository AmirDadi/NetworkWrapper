#include <iostream>
#include "Socket.h"

using namespace std;

int main(){
	Socket master_socket;
	master_socket.bind(8888);
	master_socket.listen(3, 30);
	while(true){
		Message msg = master_socket.select();
		if(msg.get_type() == NEW_CONNECTION){
			cout << "New Connection" << endl;
			master_socket.send(msg.get_sender(), "hello");
		}
		else{
			for(int i=0; i<master_socket.clients_size(); i++){
				int sd = master_socket.get_client_socket(i);	
				string read_data = master_socket.read(sd);
				cout << read_data << endl;
				master_socket.send(sd, read_data);
			}
		}
	}
}
