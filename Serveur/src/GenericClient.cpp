#include "GenericClient.hpp"

GenericClient::~GenericClient()
{
}

sf::Socket::Status GenericClient::connect(std::string address, int port) {
	sf::Socket::Status stat = socket.connect(address, port);
	socket.setBlocking(false);

	std::string data;
	while ((data = receive()) == "###NO MESSAGE RECEIVED, TRY AGAIN###");

	if (id.length() > 0) { //ID set by user
		auto serverReply = cmdFormat::parseCommand(data);
	}

	return stat;
}

std::string GenericClient::receive() {
	char buffer[MAX_NET_BUFFER_LENGTH];
	size_t length;
	std::string msg ("###NO MESSAGE RECEIVED, TRY AGAIN###");
	sf::Socket::Status status = socket.receive(buffer, MAX_NET_BUFFER_LENGTH, length);
	if (status == sf::Socket::Done) {
		msg = buffer;
	}

	return msg;
}

sf::Socket::Status GenericClient::send(const std::string& msg) {
	return socket.send(msg.c_str(), msg.length());
}