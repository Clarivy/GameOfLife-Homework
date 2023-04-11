#include <memory>
#include <assert.h>
#include "GameManager.h"

const int gridWidth = 25;
const int gridHeight = 25;

int main(int argc, char *argv[])
{
    assert(argc == 2);
    std::string rule_type = argv[1];

    GameWorld world = GameWorld(gridWidth, gridHeight, rule_type);
    GameManager gameManager(std::make_shared<GameWorld>(world));

    gameManager.StartGame();
    
    return 0;
}