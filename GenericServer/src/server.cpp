#include "GenericServer.hpp"

int main()
{
	GenericServer server;

	while (server.isAlive())
	{
		auto data = server.receive();

		for (const auto &it : data)
		{
			auto cmd = cmdFormat::parseCommand(it.second);

			if (!cmd.command.compare("say"))
			{
				std::cout << it.first << " to " << cmd.id << " : ";
				for (const auto &it : cmd.args)
				{
					std::cout << it;
				}
				std::cout << std::endl;
			}
		}
	}

	return 0;
}