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

CellPointer LifeRuleBase::DetermineNextState(const CellPointer current, const CellNeighbors &neighbors)
{
    const int count_alive = CountAliveNeighbors(neighbors);
    if (current->IsAlive() && (!BASE_CELL_SURVIVE_CONDITION.count(count_alive)))
    {
        return CreateCell(current->GetX(), current->GetY(), BASE_CELL_DEAD);
    }
    if (!current->IsAlive() && BASE_CELL_BIRTH_CONDITION.count(count_alive))
    {
        return CreateCell(current->GetX(), current->GetY(), BASE_CELL_ALIVE);
    }
    return current;
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

CellPointer LifeRuleBase::CreateCell(const int x, const int y, const char type) const
{
    switch (std::toupper(type))
    {
    case BASE_CELL_ALIVE:
        return std::make_shared<CellBase>(x, y, CellState::ALIVE);
    case BASE_CELL_DEAD:
        return std::make_shared<CellBase>(x, y, CellState::DEAD);
    default:
        return std::make_shared<CellBase>(x, y, CellState::DEAD);
    }
}

CellPointer LifeRuleColorised::DetermineNextState(const CellPointer current, const CellNeighbors &neighbors)
{
    int count_blue = 0;
    int count_red = 0;
    for (auto neighbor : neighbors)
    {
        auto neighbor_colorised = std::dynamic_pointer_cast<CellColorised>(neighbor);
        if (neighbor_colorised->IsAlive())
        {
            if (neighbor_colorised->GetColor() == CellColor::BLUE)
            {
                ++count_blue;
            }
            else if (neighbor_colorised->GetColor() == CellColor::RED)
            {
                ++count_red;
            }
        }
        else
        {
            continue;
        }
    }
    int count_alive = count_blue + count_red;
    if (current->IsAlive() && BASE_CELL_SURVIVE_CONDITION.count(count_alive))
    {
        return current;
    }
    if (!current->IsAlive() && BASE_CELL_BIRTH_CONDITION.count(count_alive))
    {
        return CreateCell(current->GetX(), current->GetY(), count_blue > count_red ? COLOR_CELL_BLUE : COLOR_CELL_RED);
    }
    return CreateCell(current->GetX(), current->GetY(), COLOR_CELL_DEAD);
}

CellPointer LifeRuleColorised::CreateCell(const int x, const int y, const char type) const
{
    switch (std::toupper(type))
    {
    case COLOR_CELL_BLUE:
        return std::make_shared<CellColorised>(x, y, CellState::ALIVE, CellColor::BLUE);
    case COLOR_CELL_RED:
        return std::make_shared<CellColorised>(x, y, CellState::ALIVE, CellColor::RED);
    case COLOR_CELL_DEAD:
    default:
        return std::make_shared<CellColorised>(x, y, CellState::DEAD, CellColor::NONE);
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

CellPointer LifeRuleGenerations::DetermineNextState(const CellPointer current, const CellNeighbors &neighbors)
{
    const int count_alive = CountAliveNeighbors(neighbors);
    auto current_generations = std::dynamic_pointer_cast<CellGenerations>(current);
    if (!current_generations->IsAlive() && BASE_CELL_BIRTH_CONDITION.count(count_alive))
    {
        return CreateCell(current_generations->GetX(), current_generations->GetY(), BASE_CELL_ALIVE);
    }
    if (current_generations->IsAlive() && current_generations->GetGeneration() == 1)
    {
        if (BASE_CELL_SURVIVE_CONDITION.count(count_alive))
        {
            auto new_cell = std::make_shared<CellGenerations>(*current_generations);
            new_cell->IncrementGeneration();
            return new_cell;
        }
        return current_generations;
    }
    if (current_generations->IsAlive() && current_generations->GetGeneration() > 1)
    {
        auto new_cell = std::make_shared<CellGenerations>(*current_generations);
        new_cell->IncrementGeneration();
        return new_cell;
    }
    return current_generations;
}

CellPointer LifeRuleGenerations::CreateCell(const int x, const int y, const char type) const
{
    switch (std::toupper(type))
    {
    case BASE_CELL_ALIVE:
        return std::make_shared<CellGenerations>(x, y, CellState::ALIVE);
    default:
        return std::make_shared<CellGenerations>(x, y, CellState::DEAD);
    }
}

CellPointer LifeRuleWeighted::DetermineNextState(const CellPointer current, const CellNeighbors &neighbors)
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
        return CreateCell(current->GetX(), current->GetY(), BASE_CELL_DEAD);
    }
    if (!current->IsAlive() && WEIGHTED_CELL_BIRTH_CONDITION.count(weighted_alive))
    {
        return CreateCell(current->GetX(), current->GetY(), BASE_CELL_ALIVE);
    }
    return current;
}
