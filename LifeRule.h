#ifndef LIFERULE_H__
#define LIFERULE_H__

#include <vector>
#include "LifeSprite.h"

// Sprite Neighbors
using SpriteNeighbors = std::vector<SpriteBase>;

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
     * Determines the next state of a cell based on the current state and the number of live neighbors
     *
     * @param current The current state of the cell
     * @param neighborse All the neighbors of the cell
     * @return The next state of the cell
     */

    virtual SpritePointer DetermineNextState(const SpritePointer current, const SpriteNeighbors &neighbors) const = 0;

    virtual SpriteNeighbors AcquireNeighbors(const WorldMap2d &map, const int x, const int y) const;
};

class LifeRuleColorised : public LifeRuleBase
{
};

class LifeRuleExtended : public LifeRuleBase
{
};

class LifeRuleGenerations : public LifeRuleBase
{
};

class LifeRuleWeighted : public LifeRuleExtended
{
};

#endif