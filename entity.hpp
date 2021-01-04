#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <map>
#include <string>
#include <vector>

class Component;
class EntityManager;

class Entity {
private:
  bool isActive;
  std::map<const std::type_info *, Component *> components;

public:
  std::string name;
  Entity();
  Entity(std::string name);

  void Update(float deltaTime);
  void Render();
  void Destroy();
  bool IsActive() const;

  template <typename T, typename... TArgs> T &AddComponent(TArgs &&...args) {
    T *component(new T(std::forward<TArgs>(args)...));
    component->owner = this;
    components[&typeid(*component)] = component;
    component->Initialize();
    return *component;
  }

  template <typename T> T *GetComponent() {
    return static_cast<T *>(components[&typeid(T)]);
  }

  // template <typename T> bool HasComponent() const {
  //  return components.find(
  //}

  void ListAllComponents() const;
};
#endif
