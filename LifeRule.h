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
     * @brief Count the number of alive neighbors
     * 
     * @param neighbors 
     * @return int 
     */
    int CountAliveNeighbors(const CellNeighbors &neighbors) const;

    /**
     * @brief Determines the next state of a cell based on the current state and the number of live neighbors
     *
     * 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
     * 2. Any live cell with two or three live neighbours lives on to the next generation.
     * 3. Any live cell with more than three live neighbours dies, as if by over-population.
     * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
     *
     * @param current The current state of the cell
     * @param neighborse All the neighbors of the cell
     * @return The next state of the cell
     */
    virtual CellPointer DetermineNextState(const CellPointer current, const CellNeighbors &neighbors);

    /**
     * @brief Get neighbors from map
     *
     * @param map The current map
     * @param x Row coordinate
     * @param y Col coordinate
     * @return CellNeighbors, vector of cells
     */
    virtual CellNeighbors GetNeighbors(const GameWorld * const game_world, const int x, const int y) const;

    /**
     * @brief Create a Cell object based on the type
     * 
     * 'O' stands for alive
     * '.' stands for dead
     *
     * @param x position of the cell
     * @param y position of the cell
     * @param type a char, indicate its type
     * @return CellPointer, created cell
     */
    virtual CellPointer CreateCell(const int x, const int y, const char type);
    
};

class LifeRuleColorised : public LifeRuleBase
{
    /**
     * @brief New born cell is based on the color of its neighbors
     *
     * @param current
     * @param neighbors
     * @return CellPointer
     */
    virtual CellPointer DetermineNextState(const CellPointer current, const CellNeighbors &neighbors) override;
    
    /**
     * @brief Create a Cell object based on the type
     * 
     * 'R' and 'B' stand for alive, where R stands for red and B stands for blue
     * '.' stands for dead
     *
     * @param x position of the cell
     * @param y position of the cell
     * @param type a char, indicate its type
     * @return CellPointer, created cell
     */
    virtual CellPointer CreateCell(const int x, const int y, const char type) override;
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
    virtual CellNeighbors GetNeighbors(const GameWorld * const game_world, const int x, const int y) const override;
};

class LifeRuleGenerations : public LifeRuleBase
{
    /**
     * @brief Check if the cell should be kept alive
     * 
     * @param count_alive 
     * @return true 
     * @return false 
     */
    bool CheckKeepLive(const int count_alive) const { return (count_alive >= GENERATIONS_CELL_THRES_LOWER) && (count_alive <= GENERATIONS_CELL_THRES_UPPER); }

    /**
     * @brief New born cell is based on the color of its neighbors
     *
     * @param current
     * @param neighbors
     * @return CellPointer
     */
    virtual CellPointer DetermineNextState(const CellPointer current, const CellNeighbors &neighbors) override;
    
    /**
     * @brief Create a Cell object based on the type
     * 
     * The number of generation of the created cell is 1.
     *
     * @param x position of the cell
     * @param y position of the cell
     * @param type a char, indicate its type
     * @return CellPointer, created cell
     */
    virtual CellPointer CreateCell(const int x, const int y, const char type) override;
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

    /**
     * @brief New born cell is based on the color of its neighbors
     *
     * @param current
     * @param neighbors
     * @return CellPointer
     */
    virtual CellPointer DetermineNextState(const CellPointer current, const CellNeighbors &neighbors) override;
};

using LifeRulePointer = std::shared_ptr<LifeRuleBase>;

#endif