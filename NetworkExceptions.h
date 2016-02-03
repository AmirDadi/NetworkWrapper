#ifndef DADI_NETWORK_EXCEPTIONS
#define DADI_NETWORK_EXCEPTIONS

#include <string>
class NetworkException{
public:
	NetworkException (std::string msg):  error(msg) {}
	std::string what() { return error; } 
private:	
	std::string error;
};

class SocketCreateException : public NetworkException{
public:
	SocketCreateException (std::string msg) : NetworkException(msg) {}
};

class BindingException : public NetworkException{
public:
	BindingException(std::string msg) : NetworkException(msg) {}
};

class ListeningException: public NetworkException{
public:
	ListeningException(std::string msg) : NetworkException(msg) {}
};

class SelectingException : public NetworkException{
public:
	SelectingException(std::string msg) : NetworkException(msg) {} 
};
#endif 
