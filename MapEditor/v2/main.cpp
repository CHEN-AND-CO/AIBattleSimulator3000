
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.hpp"


int main(int argc, char *argv[])
{
    Map themap("testmap.gmf");

    std::cout << themap << '\n';

    return 0;
}