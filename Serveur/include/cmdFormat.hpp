#ifndef CMDFORMAT_HPP
#define CMDFORMAT_HPP

#include <iostream>
#include <string>
#include <vector>

namespace cmdFormat {
	struct cmdFormat {
		std::string id, command;
		std::vector<std::string> args;
		int arglen;
		bool valid;
	};

	cmdFormat parseCommand(std::string entry);
	void printCommand(cmdFormat cmd);
	void clearCommand(cmdFormat& cmd);
	std::vector<std::string> split(const std::string& in, const char& token);
}

static const unsigned int MAX_NET_BUFFER_LENGTH = 65536;

#endif /* CMDFORMAT_HPP */

