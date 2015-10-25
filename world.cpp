#include "world.hpp"

std::size_t World::getFreeIndex() {
   auto it = std::find(used.begin(), used.end(), false);
   ++numberEntities;
   if(it == used.end()) {
       children.emplace_back(std::vector<std::shared_ptr<World>>());
       componentsUsed.emplace_back(std::vector<bool>(mIndexComponents.size(), false));
       used.emplace_back(true);

       for(auto &componentsVector : mComponentsVectors)
           componentsVector->increaseSize();

       return used.size() - 1;
   }

    else {
        *it = true;
        return std::distance(used.begin(), it);
    }
}
