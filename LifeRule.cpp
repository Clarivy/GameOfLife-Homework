#include "LifeRule.h"
#include "GameWorld.h"
#include "GameSettings.h"

CellPointer LifeRuleBase::DetermineNextState(const CellPointer current, const CellNeighbors &neighbors)
{
    int count_alive = 0;
    for (auto neighbor : neighbors)
    {
        if (neighbor->IsAlive())
        {
            ++count_alive;
        }
    }
    if (current->IsAlive() && BASE_CELL_SURVIVE.count(count_alive))
    {
        return current;
    }
    if (!current->IsAlive() && BASE_CELL_BIRTH.count(count_alive))
    {
        return std::make_shared<CellBase>(current->GetX(), current->GetY(), CellState::ALIVE);
    }
    return std::make_shared<CellBase>(current->GetX(), current->GetY(), CellState::DEAD);
}

CellNeighbors LifeRuleBase::GetNeighbors(const GameWorld const *game_world, const int x, const int y) const
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

CellPointer LifeRuleBase::CreateCell(const int x, const int y, const char type)
{
    switch (type)
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
    if (current->IsAlive() && BASE_CELL_SURVIVE.count(count_alive))
    {
        return current;
    }
    if (!current->IsAlive() && BASE_CELL_BIRTH.count(count_alive))
    {
        if (count_blue > count_red)
        {
            return std::make_shared<CellColorised>(current->GetX(), current->GetY(), CellState::ALIVE, CellColor::BLUE);
        }
        else
        {
            return std::make_shared<CellColorised>(current->GetX(), current->GetY(), CellState::ALIVE, CellColor::RED);
        }
    }
    return std::make_shared<CellColorised>(current->GetX(), current->GetY(), CellState::DEAD, CellColor::NONE);
}

CellPointer LifeRuleColorised::CreateCell(const int x, const int y, const char type)
{
    switch (type)
    {
    case BASE_CELL_BLUE:
        return std::make_shared<CellColorised>(x, y, CellState::ALIVE, CellColor::BLUE);
    case BASE_CELL_RED:
        return std::make_shared<CellColorised>(x, y, CellState::ALIVE, CellColor::RED);
    case BASE_CELL_DEAD:
        return std::make_shared<CellColorised>(x, y, CellState::DEAD, CellColor::NONE);
    default:
        return std::make_shared<CellColorised>(x, y, CellState::DEAD, CellColor::NONE);
    }
}
