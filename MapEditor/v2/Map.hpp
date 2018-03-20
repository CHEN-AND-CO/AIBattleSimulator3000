#ifndef __INC_MAP
#define __INC_MAP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Material.hpp"
#include "Tile.hpp"

class Map
{
public:
    Map(int h, int w, int tilesz);
    Map(std::string filepath);

    int getWidth() const;
    int getHeight() const;

    Tile getTile(int x, int y) const;
    void setTile(int x, int y, Tile newTile);

    //void resize(int nw, int nh);
    bool save(std::string filepath);
    //std::string getJSON() const;

    ~Map();
    
private:
    std::vector<std::vector<Tile>> maep;
    std::vector<Material> materials;
    std::string name;
    bool isTore;
    int tilesize;

};

#endif //__INC_MAP
