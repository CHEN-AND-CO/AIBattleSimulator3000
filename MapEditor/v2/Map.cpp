#include "Map.hpp"

//TODO : écrire de la merde par ici

Map::Map(int h, int w, int tilesz) : tilesize(tilesz)
{
    for ( int i ; i < h ; ++i)
    {
        std::vector<Tile> tmp;
        maep.push_back(tmp);
        for( int j ; j < w ; ++j )
        {
            maep[i].push_back(Tile(j,i));
        }
    }
}

Map::Map(std::string filepath)
{
    int width, height;
    std::ifstream file(filepath);
    nlohmann::json json_map;
    
    file >> json_map;

    name = json_map["name"];
    tilesize = json_map["tilesize"];
    //width = json_map["width"];
    //height = json_map["height"];

    std::vector<std::vector<int>> tmp = json_map["map"];

    for ( int i = 0 ; i < tmp.size() ; ++i )
    {
        std::vector<Tile> tmpline;
        maep.push_back(tmpline);

        for ( int j = 0 ; j < tmp[i].size() ; ++j )
        {
            maep[i].push_back(Tile(j, i, (char)tmp[i][j]));
        }
    }
    std::cout << "Map " << name << " loaded, tile size :" << tilesize << '\n';
}

int Map::getHeight() const
{
    return maep.size();
}

int Map::getWidth() const
{
    return maep[0].size();
}

Tile Map::getTile(int x, int y) const
{
    return maep[y][x];
}

void Map::setTile(int x, int y, Tile newTile)
{
    maep[y][x] = newTile;
}

bool Map::save(std::string filepath)
{
    std::ofstream file(filepath);

    file << "lol ca marche\n";

    return false;
}

Map::~Map()
{
    std::cout << "Map détruite\n";
}