#ifndef __INC_TILE
#define __INC_TILE

#include "Material.hpp"

class Tile  //a voir si ca peut servir, comment l'interfacer avec l'ECS
{
public:
    Tile(int nx, int ny) : x(nx), y(ny)
    { 
        Material(0, "", ""); 
        material = 0;
    }

    Tile(int nx, int ny, char nmater) : x(nx), y(ny), material(nmater) {}

    int getX() { return x; }
    int getY() { return y; }
    char getMaterial() { return material; }

private:
    int x;
    int y;
    char material;
};

#endif
