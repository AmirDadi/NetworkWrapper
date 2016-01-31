#include <iostream>
#include "ServerSocket.h"

using namespace std;

int main(){
	ServerSocket server(8888);
	server.run();
}
