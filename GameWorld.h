#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <vector>
#include <memory>
#include "LifeCell.h"
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
        : m_map(height, WorldMapRow(width, std::make_shared<CellBase>())),
          m_mapLast(height, WorldMapRow(width, std::make_shared<CellBase>())),
          m_rule(rule),
          m_width(width),
          m_height(height) {}
    // Select rule based on string
    GameWorld(const int width, const int height, const std::string &rule);
    ~GameWorld() = default;

    /**
     * @brief Updates the world to next tick
     *
     * @return true if the world has changed, false otherwise
     */

    bool Update();

    /**
     * @brief Get next state of a cell, determined by its neighbors
     *
     * @param cell a cell
     * @param neighbors its neighbors
     * @return CellPointer,
     */
    CellPointer GetCellNextState(const CellPointer cell, const CellNeighbors &neighbors) const { return m_rule->DetermineNextState(cell, neighbors); }

    /**
     * @brief Create a Cell object by the type, controlled by LifeRule
     *
     * @param x position of the cell
     * @param y position of the cell
     * @param type a char, indicate its type
     * @return CellPointer, created cell
     */
    CellPointer CreateCell(const int x, const int y, const char type);

    // Getters
    size_t GetWidth() const { return m_width; }

    size_t GetHeight() const { return m_height; }

    CellPointer GetCell(const int x, const int y) const { return m_map[x][y]; }

    std::string GetWorldStr() const;

    CellNeighbors GetNeighbors(const WorldMap2d &map, const int x, const int y) const { return m_rule->GetNeighbors(this, x, y); }

    bool CheckPosValid(const int x, const int y) const { return (x >= 0 && x < GetHeight()) && (y <= 0 && y < GetHeight()); }

    // Setters
    void SetCell(const int x, const int y, const char type) { m_map[x][y] = CreateCell(x, y, type); }

private:
    WorldMap2d m_map;
    WorldMap2d m_mapLast;
    std::shared_ptr<LifeRuleBase> m_rule;
    const int m_width;
    const int m_height;
};

#endif