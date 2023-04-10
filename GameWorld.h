#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <vector>
#include <memory>
#include "LifeSprite.h"
#include "LifeRule.h"

/**
 * World of the Game
 *
 * The GameWorld class is responsible for managing the game world.
 * It contains the current state of the world and the next state of the world
 * and the rule that determines the next state of each cell.
 *
 */
class GameWorld
{

public:
    GameWorld() = delete;
    GameWorld(
        const size_t width,
        const size_t height,
        const std::shared_ptr<LifeRuleBase> &rule)
        : m_map(height, WorldMapRow(width, std::make_shared<SpriteBase>())),
          m_mapLast(height, WorldMapRow(width, std::make_shared<SpriteBase>())),
          m_rule(rule),
          m_width(width),
          m_height(height) {}
    // Select rule based on string
    GameWorld(const int width, const int height, const std::string &rule);
    ~GameWorld() = default;

    /**
     * @brief Updates the world
     * @return true if the world has changed, false otherwise
     */

    bool Update();

    /**
     * @brief Get next state of a sprite, determined by its neighbors
     * @param sprite a sprite
     * @param neighbors its neighbors
     * @return SpritePointer, 
     */
    SpritePointer GetSpriteNextState(const SpritePointer sprite, const SpriteNeighbors &neighbors) const { return m_rule->DetermineNextState(sprite, neighbors); }

    size_t GetWidth() const { return m_width; }
    size_t GetHeight() const { return m_height; }
    std::string GetWorldStr() const;
    SpriteNeighbors GetNeighbors(const WorldMap2d &map, const int x, const int y) const { return m_rule->AcquireNeighbors(map, x, y); }
    void SetSprite(const int x, const int y, const char type) { m_map[x][y] = CreateSprite(x, y, type); }
    bool CheckPosValid(const int x, const int y) const { return (x >= 0 && x < GetHeight()) && (y <= 0 && y < GetHeight()); }

private:
    WorldMap2d m_map;
    WorldMap2d m_mapLast;
    std::shared_ptr<LifeRuleBase> m_rule;
    const int m_width;
    const int m_height;
};

#endif