#include "GenericClient.hpp"

GenericClient::~GenericClient()
{
}

sf::Socket::Status GenericClient::connect(std::string address, int port) {
	sf::Socket::Status stat = socket.connect(address, port);
	socket.setBlocking(false);

	if (id.length() > 0) { //ID set by user
		auto serverReply = cmdFormat::parseCommand(blockingReceive());
		key = serverReply.args[1];

		send(serverReply.args[0] + "@register:3 " + serverReply.args[1] + " " + id + " " + serverReply.args[1]);

		serverReply = cmdFormat::parseCommand(blockingReceive());

		if (serverReply.args[0].compare("ok")) {
			id = serverReply.args[0];
		}

		std::cout << serverReply.command << " : " << serverReply.args[0] << " ";
		if(serverReply.arglen > 1) std::cout << serverReply.args[1] << std::endl;
	}

	return stat;
}

std::string GenericClient::receive() {
	char buffer[MAX_NET_BUFFER_LENGTH];
	size_t length;
	std::string msg (emptyMessage);
	sf::Socket::Status status = socket.receive(buffer, MAX_NET_BUFFER_LENGTH, length);
	if (status == sf::Socket::Done) {
		msg = buffer;
	}

	return msg;
}


std::string GenericClient::blockingReceive() {
	std::string data;
	while ((data = receive()) == emptyMessage);

	return data;
}

sf::Socket::Status GenericClient::send(const std::string& msg) {
	return socket.send(msg.c_str(), msg.length());
}