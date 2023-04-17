#include <cctype>
#include "LifeRule.h"
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

void LifeRuleColorised::DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors)
{
    int count_blue = 0;
    int count_red = 0;
    for (auto neighbor : neighbors)
    {
        if (neighbor->IsAlive())
        {
            if (neighbor->GetState() == CELL_STATE_BLUE)
                ++count_blue;
            else if (neighbor->GetState() == CELL_STATE_RED)
                ++count_red;
        }
        else
            continue;
    }
    int count_alive = count_blue + count_red;
    if (!current->IsAlive() && BASE_CELL_BIRTH_CONDITION.count(count_alive))
    {
        current->SetState(count_blue > count_red ? CELL_STATE_BLUE : CELL_STATE_RED);
        return;
    }
    if (current->IsAlive() && (!BASE_CELL_SURVIVE_CONDITION.count(count_alive)))
    {
        current->SetState(CELL_STATE_DEAD);
        return;
    }
}

CellNeighbors LifeRuleExtended::GetNeighbors(const GameWorld *const game_world, const int x, const int y) const
{
    CellNeighbors neightbors;
    for (int i = -2; i <= 2; ++i)
    {
        for (int j = -2; j <= 2; ++j)
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

void LifeRuleGenerations::DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors)
{
    const int count_alive = CountAliveNeighbors(neighbors);
    if (!current->IsAlive() && BASE_CELL_BIRTH_CONDITION.count(count_alive))
        return current->SetState(1);
    if (current->GetState() == 1 && (!BASE_CELL_SURVIVE_CONDITION.count(count_alive)))
        current->IncreaseState();
    else if (current->GetState() > 1)
        current->IncreaseState();
    if (current->GetState() >= MAX_GENERATIONS)
        current->SetState(CELL_STATE_DEAD);
}

void LifeRuleWeighted::DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors)
{
    int weighted_alive = 0;
    for (auto neighbor : neighbors)
    {
        if (neighbor->IsAlive())
        {
            weighted_alive += 1;
            if (GetCellDistance(current, neighbor) <= 2)
            {
                weighted_alive += 1;
            }
        }
    }
    if (current->IsAlive() && (!WEIGHTED_CELL_SURVIVE_CONDITION.count(weighted_alive)))
    {
        current->SetState(CELL_STATE_DEAD);
    }
    if (!current->IsAlive() && WEIGHTED_CELL_BIRTH_CONDITION.count(weighted_alive))
    {
        current->SetState(CELL_STATE_ALIVE);
    }
}
