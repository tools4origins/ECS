#include <iostream>
#include "entity.hpp"
using namespace std;

struct Position {
    Position() = default;
    Position(int x, int y) : x(x), y(y) {}

    int x = 0, y = 0;
};

Position operator+(Position const &a, Position const &b) {
    Position r(a);
    r.x += b.x;
    r.y += b.y;
    return r;
}

char map[5][5] = {{'O', 'O', 'O', 'O', 'O'},{'O', 'O', 'O', 'O', 'O'},{'O', 'O', 'O', 'O', 'O'},{'O', 'O', 'O', 'O', 'O'},{'O', 'O', 'O', 'O', 'O'}};

class RenderSystem {
public:
    void run(std::shared_ptr<World> world, Position const &pos = Position()) {

        std::vector<Position> &refPosition = world->getComponentsVector<Position>();
        std::vector<char> &refChars = world->getComponentsVector<char>();
        std::size_t indexPos = world->getIndexComponent<Position>();
        std::size_t indexChar = world->getIndexComponent<char>();

        for(auto i = 0; i < world->numberEntities; ++i)
            if(world->used[i]) // If entity exists
                if(world->componentsUsed[i][indexPos]) // If entity owns position
                    if(world->componentsUsed[i][indexChar]) // If entity owns a char
                        map[refPosition[i].y + pos.y][refPosition[i].x + pos.x] = refChars[i];

        // For children : terminal recursion is the best way
        for(auto i = 0; i < world->numberEntities; ++i)
            if(world->used[i])
                for(auto &child : world->children[i])
                    run(child, pos + refPosition[i]);
    }
};

int main()
{
    auto world = std::make_shared<World>();

    // characterC is a treeA's child
    auto treeA = createEntity(world);
    auto treeB = createEntity(world);
    auto characterC = createEntity(treeA);

    treeA.addComponent<char>('A');
    treeB.addComponent<char>('B');
    characterC.addComponent<char>('C');

    treeA.addComponent<Position>(2, 1);
    treeB.addComponent<Position>(1, 1);
    characterC.addComponent<Position>(1, 1);

    RenderSystem().run(world);

    for(auto j = 0; j < 5; ++j) {
        for(auto i = 0; i < 5; ++i)
            std::cout << map[j][i] << " ";
        std::cout << std::endl;
    }

    return 0;
}

