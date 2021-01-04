#include "./entity.hpp"
#include "./components/component.hpp"
#include <iostream>

Entity::Entity() : isActive(true) {}

Entity::Entity(std::string name) : name(name), isActive(true) {}

void Entity::Update(float deltaTime) {
  for (auto const &[key, component] : components) {
    if (isActive)
      component->Update(deltaTime);
  }
}

void Entity::Render() {
  for (auto const &[key, component] : components) {
    if (isActive)
      component->Render();
  }
}

void Entity::Destroy() { this->isActive = false; }

bool Entity::IsActive() const { return this->isActive; }

void Entity::ListAllComponents() const {
  for (auto const &[key, component] : components) {
    std::cout << key->name() << std::endl;
  }
}
