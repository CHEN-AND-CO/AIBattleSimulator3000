#include "GenericServer.hpp"



GenericServer::GenericServer(const int port)
{
	listener.listen(port);
	listener.setBlocking(false);

	alive = true;
}

GenericServer::~GenericServer()
{
}

void GenericServer::send(const std::string id, const std::string& msg) {
	auto tmp = clients[id];
	if (!tmp) {
		std::cout << "Client " << id << " not found !" << std::endl;
	}

	tmp->socket->send(msg.c_str(), msg.length());
}


void GenericServer::receive() {
	std::shared_ptr<sf::TcpSocket> nextClient = std::make_shared<sf::TcpSocket>();
	nextClient->setBlocking(false);

	if (listener.accept(*nextClient) == sf::Socket::Done) {
		ClientData tmp = { alphaNumericGeneration(16), nextClient };
		clients.insert(std::make_pair(std::to_string(clients.size()), std::make_shared<ClientData>(tmp)));

		send(std::to_string(clients.size() - 1), std::string(server_id) + std::string("@auth:1 ") + std::to_string(clients.size() - 1));

		std::cout << clients.size() - 1 << " is connected\n";
	}

	receivePackets();
}

void GenericServer::receivePackets() {
	char buffer[MAX_NET_BUFFER_LENGTH];
	size_t length;
	sf::Socket::Status status;
	std::vector<std::map<std::string, std::shared_ptr<ClientData>>::iterator> list;

	for (auto it = clients.begin(); it != clients.end(); ++it) {
		status = it->second->socket->receive(buffer, MAX_NET_BUFFER_LENGTH, length);

		switch (status) {
		case sf::Socket::Done:
			message = buffer;
			std::cout << it->first << ": " << message << "\n";
			if (message.length() > 0) {
				action(it->first, message);
				message.clear();
				for (int i = 0; i < MAX_NET_BUFFER_LENGTH; i++) {
					buffer[i] = 0;
				}
			}
			break;
		case sf::Socket::Disconnected:
			std::cout << it->first << " has been disconnected\n";
			list.push_back(it);
			break;

		default:
			break;
		}
	}

	for (auto i = 0; i < (int)list.size(); i++) {
		clients.erase(list[i]);
	}
}

void GenericServer::action(std::string id, std::string msg) {
	auto cmd = parseCommand(msg);

	if (!cmd.command.compare("quit")) {
		alive = false;
	}
	else if (!cmd.command.compare("say")) {
		std::cout << id << " to " << cmd.id << " : ";
		for (const auto &it : cmd.args) {
			std::cout << it;
		}
		std::cout << std::endl;
	}
}


commandForm GenericServer::parseCommand(std::string entry) {
	commandForm out;
	out.id = "";
	out.command = "";

	std::vector<std::string> tmp;
	std::string stmp;

	tmp = split(entry, ' ');
	stmp = tmp[0];
	tmp.erase(tmp.begin());
	out.args = tmp;
	tmp.clear();

	tmp = split(stmp, '@');
	if (tmp.size() > 0) out.id = tmp[0];
	if (tmp.size() > 1) out.command = tmp[1];
	tmp.clear();

	tmp = split(out.command, ':');
	if (tmp.size() > 0) out.command = tmp[0];
	if (tmp.size() > 1) out.arglen = std::atoi(tmp[1].c_str());
	tmp.clear();

	if (out.id.length() < 1 || out.command.length() < 1 || out.arglen < 0) {
		out.valid = false;
	} else {
		out.valid = true;
	}

	return out;
}


void GenericServer::printCommand(commandForm cmd) {
	if (cmd.valid) {
		std::cout << "id : " << cmd.id << std::endl;
		std::cout << "command : " << cmd.command << std::endl;
		std::cout << "arglen : " << cmd.arglen << std::endl;
		for (auto& ref : cmd.args) {
			std::cout << ref << "\t";
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "Not a valid Command format" << std::endl;
	}
}

void GenericServer::clearCommand(commandForm& cmd) {
	cmd.args.clear();
	cmd.arglen = -1;
	cmd.command.clear();
	cmd.id.clear();
	cmd.valid = false;
}


std::string GenericServer::alphaNumericGeneration(std::string::size_type length) {
	std::string charset =	"0123456789"
			"abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::default_random_engine generator{ std::random_device{}() };
	std::uniform_int_distribution<std::string::size_type> distribution(0, charset.length() - 2);

	std::string out;
	out.reserve(length);

	while (length--) {
		out += charset[distribution(generator)];
	}

	return out;
}

std::vector<std::string> GenericServer::split(const std::string& in, const char& token) {
	std::vector<std::string> out;
	std::string buffer;

	for (const auto &n : in) {
		if (n != token)
			buffer += n;
		else if (n == token && buffer != "") {
			out.push_back(buffer);
			buffer = "";
		}
	}
	if (buffer != "") out.push_back(buffer);

	return out;
}