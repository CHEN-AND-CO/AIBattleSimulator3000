#ifndef __INC_TILE
#define __INC_TILE

class Tile  //a voir si ca peut servir, comment l'interfacer avec l'ECS
{
public:
    Tile(int nx, int ny) : x(nx), y(ny) {}
    Tile(int nx, int ny, char nmater) : x(nx), y(ny), material(nmater) {}

    int getX() { return x; }
    int getY() { return y; }

private:
    int x;
    int y;
    char material;
};

#endif
