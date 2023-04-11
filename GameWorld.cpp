#include "GameWorld.h"

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
