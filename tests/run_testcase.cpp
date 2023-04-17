#include <memory>
#include <assert.h>
#include "../GameManager.h"

const int gridWidth = 25;
const int gridHeight = 25;
const int MAX_ROUNDS = 100;

int main(int argc, char *argv[])
{
    assert(argc == 4);
    std::string rule_type = argv[1];
    std::string input_file = argv[2];
    std::string output_file = argv[3];

    GameWorld world = GameWorld(gridWidth, gridHeight, rule_type);
    GameManager gameManager(std::make_shared<GameWorld>(world));

    if (!gameManager.LoadWorld(input_file))
    {
        return 1;
    }

    for (int i = 0; i < MAX_ROUNDS; i++)
    {
        gameManager.UpdateGame();
    }

    gameManager.SaveWorld(output_file);
    
    return 0;
}