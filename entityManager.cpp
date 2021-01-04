#include "./entityManager.hpp"
#include <iostream>

EntityManager *EntityManager::instance = nullptr;

EntityManager::EntityManager() {}

EntityManager &EntityManager::GetEntityManager() {
  if (!instance)
    instance = new EntityManager();
  return *instance;
}
void EntityManager::ClearData() {
  for (auto &entity : entities) {
    entity->Destroy();
  }
}

bool EntityManager::HasNoEntities() const { return entities.size() == 0; }

void EntityManager::Update(float deltaTime) {
  for (auto &entity : entities) {
    entity->Update(deltaTime);
  }
}

void EntityManager::Render() {
  for (auto &entity : entities) {
    entity->Render();
  }
}

Entity &EntityManager::AddEntity(std::string entityName) {
  Entity *entity = new Entity(entityName);
  entities.emplace_back(entity);
  return *entity;
}

std::vector<Entity *> EntityManager::GetEntities() const { return entities; }

unsigned int EntityManager::GetEntityCount() const { return entities.size(); }

void EntityManager::ListAllEntities() const {
  for (auto &entity : entities) {
    std::cout << "name: " << entity->name << std::endl;
    entity->ListAllComponents();
  }
}
