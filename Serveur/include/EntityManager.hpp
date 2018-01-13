#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <vector>
#include <algorithm>

class EntityManager{
private:
  std::vector<unsigned int> m_ids;
  
public:
  unsigned int getNextId();
  void removeEntity(unsigned int id);
  
  std::vector<unsigned int> getEntitiesId() const {
    return m_ids;
  }
};

#endif
