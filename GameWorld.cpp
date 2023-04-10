#include "GameWorld.h"

bool GameWorld::Update()
{
    bool isChanged = false;
    std::swap(m_mapLast, m_map);
    for (int row = 0; row < GetHeight(); ++row)
    {
        for (int col = 0; col < GetWidth(); ++col)
        {
            const auto neighbors = GetNeighbors(m_mapLast, row, col);
            m_map[row][col] = GetSpriteNextState(m_mapLast[row][col], neighbors);
        }
    }
}

std::string GameWorld::GetWorldStr() const {
    std::string world_str;
    for(const WorldMapRow &row: m_map) {
        for (const SpritePointer &sprite: row) {
            world_str += sprite->GetStr();
        }
        world_str += '\n';
    }
    return world_str;
}