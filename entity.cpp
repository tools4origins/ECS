#include "entity.hpp"

Entity::Entity(std::shared_ptr<World> world, std::size_t index) :
    std::tuple<std::shared_ptr<World>, std::size_t>(world, index){}

Entity createEntity(const Entity &entity) {
    std::shared_ptr<World> world = std::make_shared<World>();
    std::get<0>(entity)->children[std::get<1>(entity)].emplace_back(world);

    return createEntity(world);
}

Entity createEntity(std::shared_ptr<World> world) {
    return Entity(world, world->getFreeIndex());
}
