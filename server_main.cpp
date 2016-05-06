#include <iostream>
#include "ServerSocket.h"

using namespace std;
#define PORT 8888

int main(){
	ServerSocket server(PORT); //Create class that inherit from ServerSocket and override event methods
	//defult: server says hello on new connection, and echo on new message (check ServerSocket.h)
	//@students: do not create any change in run method
	server.run();
}