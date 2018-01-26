#ifndef __INC_MAP
#define __INC_MAP

#include <vector>
#include <string>
#include <iostream>
#include "Tile.hpp"

class Map
{
public:
    Map(int h, int w);
    Map(std::string filepath);

    int getWidth() const;
    int getHeight() const;

    void resize(int nw, int nh);

    ~Map();
    
private:
    std::vector<std::vector<char>> map;

};

#endif //__INC_MAP
