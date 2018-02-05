#include <string>
#include "GenericClient.hpp"

int main(int argc, char **argv)
{
    std::string address("127.0.0.1");
    unsigned short port(30666);
    std::string name("");

    if (argc > 1)
    {
        address = argv[0];
    }
    if (argc > 2)
    {
        port = (unsigned int)std::atoi(argv[1]);
    }
    if (argc > 3)
    {
        name = argv[2];
    }

    GenericClient client(address, port, name);

    while (client.isAlive())
    {
        auto tp = client.receive();
        if (tp.compare(""))
        {
            auto cmd = cmdFormat::parseCommand(tp);

            if (!cmd.command.compare("say"))
            {
                std::cout << cmd.args[0] << ":" << cmd.args[1] << std::endl;
            }
        }
    }

    return 0;
}