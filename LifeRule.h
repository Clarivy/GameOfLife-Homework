#ifndef LIFERULE_H__
#define LIFERULE_H__

#include <vector>
#include "LifeCell.h"

class GameWorld;

// Cell Neighbors

/**
 * Base Class of Rules
 *
 * Determines the next state of a cell based on the current state and the number of live neighbors
 *
 */
class LifeRuleBase
{
public:
    LifeRuleBase() = default;
    virtual ~LifeRuleBase() = default;

    /**
     * @brief Determines the next state of a cell `current`, based on the current state and the number of live neighbors 
     *
     * 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
     * 2. Any live cell with two or three live neighbours lives on to the next generation.
     * 3. Any live cell with more than three live neighbours dies, as if by over-population.
     * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
     *
     * @param current A pointor to a cell to be updated
     * @param neighbors a vector of `CellPointer`, containing all the neighbors of the cell we working on. You need to count the number of living cells in neighbors to determine the next state.
     */
    virtual void DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors);

    /**
     * @brief Get neighbors from map
     *
     * @param game_world Current world,
     * @param x Row coordinate
     * @param y Col coordinate
     * @return CellNeighbors, vector of cells
     */
    virtual CellNeighbors GetNeighbors(const GameWorld *const game_world, const int x, const int y) const;

    /**
     * @brief Count the number of alive neighbors
     *
     * @param neighbors
     * @return int
     */
    virtual int CountAliveNeighbors(const CellNeighbors &neighbors) const;

    /**
     * @brief Get the Rule Name object
     *
     * @return const std::string&
     */
    virtual const std::string GetRuleName() const { return "Base"; }
};

class LifeRuleColorised : public LifeRuleBase
{
    /**
     * @brief New born cell is based on the color of its neighbors
     *
     * @param current A pointor to a cell to be updated
     * @param neighbors All the neighbors of the cell
     */
    virtual void DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors) override;

    virtual const std::string GetRuleName() const { return "Colorised"; }
};

class LifeRuleExtended : public LifeRuleBase
{
    /**
     * @brief Get the Neighbors object
     *
     * The neighbors are extended to moore neighborhood of range 2.
     *
     * @param game_world
     * @param x
     * @param y
     * @return CellNeighbors
     */
    virtual CellNeighbors GetNeighbors(const GameWorld *const game_world, const int x, const int y) const override;

    virtual const std::string GetRuleName() const { return "Extended"; }

private:
};

class LifeRuleGenerations : public LifeRuleBase
{

    virtual void DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors) override;

    virtual const std::string GetRuleName() const { return "Generations"; }
};

class LifeRuleWeighted : public LifeRuleExtended
{

    /**
     * @brief Get distance between two cells
     *
     * @param cell_x
     * @param cell_y
     * @return int
     */
    int GetCellDistance(const CellPointer cell_x, const CellPointer cell_y) const { return std::abs(cell_x->GetX() - cell_y->GetX()) + std::abs(cell_x->GetY() - cell_y->GetY()); }

    virtual void DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors) override;

    virtual const std::string GetRuleName() const { return "Weighted"; }
};

using LifeRulePointer = std::shared_ptr<LifeRuleBase>;

#endif