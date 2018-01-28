/****************************************/
/*           class Material             */
/*Defines the properties of a specified */
/*material, like grass, water, ect.     */
/****************************************/

#ifndef __INC_MATERIAL
#define __INC_MATERIAL

#include <string>

class Material
{
public:
    Material(); //Constructeur vide
    Material(char nid, std::string nname, std::string ntex) : id(nid), name(nname), texturePath(ntex) {}

    int getID() { return id; }
    std::string getName() { return name; }
    std::string getTexturePath() { return texturePath; }

protected:
    char id;                //Material ID to be used in map tiles
    std::string name;       //Material name, ex. "grass" or "patate"
    std::string texturePath;//Path to the texture to use for this Material
};

#endif //__INC_MATERIAL