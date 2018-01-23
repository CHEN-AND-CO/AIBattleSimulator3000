#pragma once

#include <SFML\Network.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include <random>

struct commandForm {
	std::string id, command;
	std::vector<std::string> args;
	int arglen;
	bool valid;
};

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

	commandForm parseCommand(std::string entry);
	void printCommand(commandForm cmd);
	void clearCommand(commandForm& cmd);

	std::string alphaNumericGeneration(std::string::size_type length);
	std::vector<std::string> split(const std::string& in, const char& token);
private:
	std::map<std::string, std::shared_ptr<ClientData>> clients;
	sf::TcpListener listener;

	bool alive;
	std::string message;

	std::string server_id = "###SERVER###";
	static const unsigned int MAX_NET_BUFFER_LENGTH = 65536;
};

