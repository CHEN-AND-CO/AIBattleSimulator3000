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
				std::string message(it.first + "@say:1 ");

				for (const auto &it : cmd.args)
				{
					if (&it != &cmd.args[0])
					{
						std::cout << " ";
						message += " ";
					}
					std::cout << it;
					message += it;
				}
				std::cout << std::endl;
				message += "\n";

				server.send(cmd.id, message);
			}
		}
	}

	return 0;
}