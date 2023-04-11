#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <vector>
#include <iostream>
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
        const int width,
        const int height,
        const std::shared_ptr<LifeRuleBase> &rule);
    // Select rule based on string
    GameWorld(const int width, const int height, const std::string &rule_type);
    ~GameWorld() = default;

    /**
     * @brief Updates the world to next tick
     *
     */
    void Update();

    /**
     * @brief Get next state of a cell, determined by its neighbors
     *
     * @param cell a cell
     * @param neighbors its neighbors
     * @return CellPointer,
     */
    CellPointer GetCellNextState(const CellPointer cell, const CellNeighbors &neighbors) const { return m_rule->DetermineNextState(cell, neighbors); }

    // Getters
    int GetWidth() const { return m_width; }

    int GetHeight() const { return m_height; }

    CellPointer GetCell(const int x, const int y) const { return m_map[x][y]; }

    // Get Rule Name
    const std::string GetRuleName() const { return m_rule->GetRuleName(); }

    std::string GetWorldStr() const;

    CellNeighbors GetNeighbors(const int x, const int y) const { return m_rule->GetNeighbors(this, x, y); }

    bool CheckPosValid(const int x, const int y) const { return (x >= 0 && x < GetHeight()) && (y >= 0 && y < GetWidth()); }

    // Setters
    void SetCell(const int x, const int y, const char type)
    {
        m_map[x][y] = m_rule->CreateCell(x, y, type);
    }

private:
    WorldMap2d m_map;
    WorldMap2d m_mapNext;
    std::shared_ptr<LifeRuleBase> m_rule;
    const int m_width;
    const int m_height;
};

#endif