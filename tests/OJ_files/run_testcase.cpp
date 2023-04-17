#include <memory>
#include <iostream>
#include <assert.h>
#include "GameManager.h"

const int gridWidth = 25;
const int gridHeight = 25;
const int MAX_ROUNDS = 100;

int main()
{
    std::string rule_type;
    std::cin >> rule_type;
    std::cin.ignore(10000, '\n');

    GameWorld world = GameWorld(gridWidth, gridHeight, rule_type);
    GameManager gameManager(std::make_shared<GameWorld>(world));

    gameManager.LoadWorld(std::cin);

    for (int i = 0; i < MAX_ROUNDS; i++)
    {
        gameManager.UpdateGame();
    }

    gameManager.SaveWorld(std::cout);
    
    return 0;
}