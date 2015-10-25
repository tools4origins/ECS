#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "world.hpp"

class Entity : public std::tuple<std::shared_ptr<World>, std::size_t> {
public:
    Entity(std::shared_ptr<World> world, std::size_t index);

    template<typename Component>
    void addComponent(Component const &component = Component()) {
        std::get<0>(*this)->addComponent<Component>();
        std::get<0>(*this)->componentsUsed[std::get<1>(*this)][std::get<0>(*this)->getIndexComponent<Component>()] = true;
        std::get<0>(*this)->getComponentsVector<Component>()[std::get<1>(*this)] = component;
    }

    template<typename Component, typename ...Args>
    void addComponent(Args&& ...args) {
        addComponent(Component(std::forward<Args>(args)...));
    }

private:
};

Entity createEntity(std::shared_ptr<World> world);
Entity createEntity(Entity const &entity);

#endif // ENTITY_HPP

