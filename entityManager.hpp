#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "./components/component.hpp"
#include "./entity.hpp"
#include <vector>

class EntityManager {
private:
  static EntityManager *instance;

  std::vector<Entity *> entities;

  EntityManager();

public:
  static EntityManager &GetEntityManager();
  void ClearData();
  void Update(float deltTime);
  void Render();
  bool HasNoEntities() const;
  Entity &AddEntity(std::string entityName);
  std::vector<Entity *> GetEntities() const;
  unsigned int GetEntityCount() const;

  void ListAllEntities() const;
};
#endif
