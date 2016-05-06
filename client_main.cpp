#include <iostream>
#include <string>
#include "Client.h"
#define PORT 8888
using namespace std;
// class MyClient : public Client{
// public:
// 	MyClient(int port) : Client(port) {};
// 	virtual void get_input(){
// 		cerr << "here" << endl;
// 		while(true){
// 			string in;
// 			cin >> in;
// 			cout << send_message(in) << endl;
// 		}
// 	}
// };

int main(){
	Client *client = new Client(PORT);
	cout << client->receive_data() << endl; //server says hello on connect 
	while(1){
		string s;
		cin >> s;

		cout << client->send_message(s) << endl;
	}
}