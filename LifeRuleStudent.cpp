#include <cctype>
#include "LifeRuleStudent.h"
#include "GameWorld.h"
#include "GameSettings.h"

int LifeRuleBase::CountAliveNeighbors(const CellNeighbors &neighbors) const
{
    int count_alive = 0;
    for (auto neighbor : neighbors)
    {
        if (neighbor->IsAlive())
        {
            ++count_alive;
        }
    }
    return count_alive;
}

void LifeRuleBase::DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors)
{
    const int count_alive = CountAliveNeighbors(neighbors);
    if (current->IsAlive() && (!BASE_CELL_SURVIVE_CONDITION.count(count_alive)))
    {
        current->SetState(CELL_STATE_DEAD);
        return;
    }
    if (!current->IsAlive() && BASE_CELL_BIRTH_CONDITION.count(count_alive))
    {
        current->SetState(CELL_STATE_ALIVE);
        return;
    }
}

CellNeighbors LifeRuleBase::GetNeighbors(const GameWorld *const game_world, const int x, const int y) const
{
    CellNeighbors neightbors;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue;
            int next_x = x + i;
            int next_y = y + j;
            if (game_world->CheckPosValid(next_x, next_y))
            {
                neightbors.push_back(game_world->GetCell(next_x, next_y));
            }
        }
    }
    return neightbors;
}
