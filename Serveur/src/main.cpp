#include "ComponentStorer.hpp"
#include "EntityManager.hpp"
#include "EntityCreator.hpp"

int main(){
  ComponentStorer c;
  EntityManager e;
  EntityCreator eC(c,e,"ressources/script/Entity.lua");

  
  
  return 0;
}
