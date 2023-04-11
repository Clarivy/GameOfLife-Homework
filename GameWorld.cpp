#include "GameWorld.h"

GameWorld::GameWorld(const int width, const int height, const std::string &rule_type)
    : m_width(width), m_height(height)
{
    m_map.resize(m_height);
    m_mapNext.resize(m_height);
    if (rule_type == "Colorised")
    {
        m_rule = std::make_shared<LifeRuleColorised>();
    }
    else if (rule_type == "Generations")
    {
        m_rule = std::make_shared<LifeRuleGenerations>();
    }
    else
    {
        m_rule = std::make_shared<LifeRuleBase>();
    }
}

bool GameWorld::Update()
{
    bool isChanged = false;
    for (int row = 0; row < GetHeight(); ++row)
    {
        for (int col = 0; col < GetWidth(); ++col)
        {
            const auto neighbors = GetNeighbors(row, col);
            m_mapNext[row][col] = GetCellNextState(m_map[row][col], neighbors);
            if (m_mapNext[row][col]->IsAlive() != m_map[row][col]->IsAlive())
            {
                isChanged = true;
            }
        }
    }
    std::swap(m_mapNext, m_map);
    return isChanged;
}

std::string GameWorld::GetWorldStr() const
{
    std::string world_str;
    for (const WorldMapRow &row : m_map)
    {
        for (const CellPointer &cell : row)
        {
            world_str += cell->GetStr();
        }
        world_str += '\n';
    }
    return world_str;
}
