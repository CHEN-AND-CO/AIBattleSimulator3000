#include "GenericServer.hpp"

int main()
{
	GenericServer server;

	while (server.isAlive())
	{
		server.receive();
	}

	return 0;
}