#include <memory>
#include "GameManager.h"

const int gridWidth = 20;
const int gridHeight = 20;

int main()
{
    GameWorld world = GameWorld(gridWidth, gridHeight, "Base");
    GameManager gameManager(std::make_shared<GameWorld>(world));

    gameManager.StartGame();
    
    return 0;
}