#ifndef WORLD_HPP
#define WORLD_HPP

#include "polymorphicvector.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <algorithm>
#include <cassert>

class Entity;

class World {
    friend Entity;
public:
    std::size_t getFreeIndex();

    template<typename Component>
    std::vector<Component> &getComponentsVector() {
        assert(mIndexComponents.find(typeid(Component)) != mIndexComponents.end());
        return std::experimental::any_cast<std::vector<Component>&>(mComponentsVectors[mIndexComponents[typeid(Component)]]->getRefVector());
    }

    template<typename Component>
    std::size_t getIndexComponent() {
        assert(mIndexComponents.find(typeid(Component)) != mIndexComponents.end());
        return mIndexComponents[typeid(Component)];
    }

    std::vector<std::vector<bool>> componentsUsed;
    std::vector<bool> used;
    std::vector<std::vector<std::shared_ptr<World>>> children;
    std::size_t numberEntities = 0;
private:
    std::unordered_map<std::type_index, std::size_t> mIndexComponents;

    std::vector<std::unique_ptr<AbstractPolymorphicVector>> mComponentsVectors;

    template<typename Component>
    void addComponent() {
        if(mIndexComponents.find(typeid(Component)) != mIndexComponents.end())
            return;

        mIndexComponents[typeid(Component)] = mComponentsVectors.size();
        mComponentsVectors.emplace_back(std::make_unique<PolymorphicVector<Component>>(numberEntities));

        for(auto &bitset : componentsUsed)
            bitset.emplace_back(false);
    }

};

#endif // WORLD_HPP

