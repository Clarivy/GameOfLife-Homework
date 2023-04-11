#include "GameWorld.h"

GameWorld::GameWorld(const int width, const int height, const std::shared_ptr<LifeRuleBase> &rule)
    : m_map(height, WorldMapRow(width)),
      m_mapNext(height, WorldMapRow(width)),
      m_rule(rule),
      m_width(width),
      m_height(height)
{
    for (int i = 0; i < GetHeight(); ++i)
    {
        for (int j = 0; j < GetWidth(); ++j)
        {
            m_map[i][j] = m_rule->CreateCell(i, j, BASE_CELL_DEAD);
        }
    }
}

GameWorld::GameWorld(const int width, const int height, const std::string &rule_type)
    : m_map(height, WorldMapRow(width)),
      m_mapNext(height, WorldMapRow(width)),
      m_width(width),
      m_height(height)
{
    if (rule_type == "Colorised")
        m_rule = std::make_shared<LifeRuleColorised>();
    else if (rule_type == "Generations")
        m_rule = std::make_shared<LifeRuleGenerations>();
    else if (rule_type == "Extended")
        m_rule = std::make_shared<LifeRuleExtended>();
    else if (rule_type == "Base")
        m_rule = std::make_shared<LifeRuleBase>();
    else
        throw std::invalid_argument("Invalid rule type");
    for (int i = 0; i < GetHeight(); ++i)
    {
        for (int j = 0; j < GetWidth(); ++j)
        {
            m_map[i][j] = m_rule->CreateCell(i, j, BASE_CELL_DEAD);
        }
    }
}

void GameWorld::Update()
{
    for (int row = 0; row < GetHeight(); ++row)
    {
        for (int col = 0; col < GetWidth(); ++col)
        {
            const auto neighbors = GetNeighbors(row, col);
            m_mapNext[row][col] = GetCellNextState(m_map[row][col], neighbors);
        }
    }
    std::swap(m_mapNext, m_map);
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
        world_str += "\n";
    }
    return world_str;
}
