#ifndef GAMESETTING_H__
#define GAMESETTING_H__

#include <set>

// For base rule save and laod
#define BASE_CELL_ALIVE 'O'
#define BASE_CELL_DEAD '.'

// For base rule states
const std::set<int> BASE_CELL_SURVIVE_CONDITION = {2, 3};
const std::set<int> BASE_CELL_BIRTH_CONDITION = {3};

// For colorised rule save and load
#define COLOR_CELL_BLUE 'B'
#define COLOR_CELL_RED 'R'
#define COLOR_CELL_DEAD '.'


// For generations rule
#define MAX_GENERATIONS 8

// For weightened rule state
const std::set<int> WEIGHTED_CELL_SURVIVE_CONDITION = {4, 5, 6};
const std::set<int> WEIGHTED_CELL_BIRTH_CONDITION = {6};


#endif