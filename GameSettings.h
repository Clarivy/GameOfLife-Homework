#ifndef GAMESETTING_H__
#define GAMESETTING_H__

#include <set>

// For base rule save and laod
#define BASE_CELL_ALIVE 'O'
#define BASE_CELL_DEAD '.'

// For base rule states
const std::set<int> BASE_CELL_SURVIVE = {2, 3};
const std::set<int> BASE_CELL_BIRTH = {3};

// For colorised rule save and load
#define COLOR_CELL_BLUE 'B'
#define COLOR_CELL_RED 'R'
#define COLOR_CELL_DEAD '.'

// For generations rule states
#define GENERATIONS_CELL_THRES_UPPER 3
#define GENERATIONS_CELL_THRES_LOWER 2
const std::set<int> GENERATIONS_CELL_BIRTH = {2, 3};

// For generations rule
#define MAX_GENERATIONS 8

// For weightened rule state
const std::set<int> WEIGHTED_CELL_SURVIVE = {4, 5, 6};
const std::set<int> WEIGHTED_CELL_BIRTH = {6};


#endif