#ifndef GENERIC_SERVER_HPP
#define GENERIC_SERVER_HPP

#include <SFML\Network.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include <random>

#include "cmdFormat.hpp"

struct ClientData {
	std::string key;
	std::shared_ptr<sf::TcpSocket> socket;
};

class GenericServer
{
public:
	GenericServer(const int port = 30666);
	~GenericServer();

	bool isAlive() const { return alive; }
	void toggleAlive() { alive = !alive; }
	void setAlive(bool parm) { alive = parm; }

	void send(const std::string id, const std::string& msg);
	void receive();
	void receivePackets();

	void action(std::string id, std::string msg);

	void reregister(std::string oldId, std::string oldKey, std::string id, std::string key);
	void login(std::string id, std::string key);

	std::string alphaNumericGeneration(std::string::size_type length);
private:
	std::map<std::string, std::shared_ptr<ClientData>> clients;
	sf::TcpListener listener;

	bool alive;
	std::string message;

	std::string server_id = "SERVER";
	static const unsigned int MAX_NET_BUFFER_LENGTH = 65536;
};

#endif /* GENERIC_SERVER_HPP */