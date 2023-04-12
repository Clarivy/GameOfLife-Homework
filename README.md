# Homework: Game Of Life

## Introduction

The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine.

![https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life](./pics/demo.gif)

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

- Any live cell with fewer than two live neighbours dies, as if by underpopulation.

- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours comes to life.

![Moreno, Niandry. "A vector-based geographical cellular automata model to mitigate scale sensitivity and to allow objects' geometric transformation." (2008).](./pics/rule.png)

The Game of Life has been studied extensively, and many interesting patterns have been discovered. Some of these patterns are stable, meaning that they will continue to exist indefinitely. Others are unstable, meaning that they will eventually die out. Still others are periodic, meaning that they will repeat themselves after a certain number of steps. Here are some basic patterns:

![http://pi.math.cornell.edu/~lipa/mec/lesson6.html](./pics/patterns.png)

More amazing patterns can be found in the [wiki](conwaylife.com). You can also play with it at [golly](https://golly.sourceforge.net/webapp/golly.html). Here is a video in [youtube](https://www.youtube.com/watch?v=C2vgICfQawE) and [bilibili](https://www.bilibili.com/video/BV1PE411d7aR) about the Game of Life for your reference.

There are many variants of the Game of Life, each with its own set of rules. Here are four of the most popular variants:

- Colorised

  The base rules followed by the original Game of Life are the same as above.

  However, the live cells have different colors. When a cell is born, it takes on the colour value of the majority of its three neighbours.

  The formal definition will be describe later. More on [wiki](https://conwaylife.com/wiki/Colourised_Life).

- Extended

  The base rules followed by the original Game of Life are the same as above.

  However, the size of a cell's neighborhood is extended to include cells with a distance greater than one.

- Weighted

  The size of a cell's neighborhood is extended to include cells with a distance greater than one. However, some neighbors might make more influence.

- Generations:

  The live cells would not dead immediately when overpopulated or underpopulated. Instead, the cells 'get older' before eventually dying.

  The formal definition will be describe later. More on [wiki](https://conwaylife.com/wiki/Generations).

## Your Task

Your task is to implement the Game of Life in C++ with multiple rules. We have provided you a framework to help you get started. You need to complete `LifeRuleStudent.cpp`. We have already wrote the base rule, `class LifeRuleBase`, left you to finish four variant rules above. There are four rules you need to implement: `LifeRuleColorised`, `LifeRuleExtended`, `LifeRuleWeighted`, `LifeRuleGenerations`. You only need to submit `LifeRuleStudent.cpp` to OJ. And you may not need to change other files in this project.

### Description

The game is often played on a infinite grid. However, to simply this project, our game has a fixed 25 \* 25 grid.

A cell in grid can be described as threer parameters: (x, y, state), where x, y are its coordinate ranged from 0 to 24, state is either live or dead. The cells that out of the finite grid will be regarded as dead, and will never come to life.

A cell is defined in `LifeCell.cpp`, called `CellBase`, with its smart pointer `CellPointer`

In `LifeRuleBase`, there are five functions:

#### DetermineNextState

```cpp
CellPointer DetermineNextState(const CellPointer current, const CellNeighbors &neighbors)
```

It determines the next state of a cell `current`, based on its state and the number of live `neighbors`.

1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.

2. Any live cell with two or three live neighbours lives on to the next generation.

3. Any live cell with more than three live neighbours dies, as if by over-population.

4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

- Parameters:
  current – The current state of the cell.
  neighbors – a vector of `CellPointer`, all the neighbors of `current`. You need count the number of live cells in neighbors to determine the next state.

- Returns:
  The next state of `current`.

#### GetNeighbors

```cpp
CellNeighbors GetNeighbors(const GameWorld *const game_world, const int x, const int y) const
```

It returns all neighbors of a cell in (x, y). For example,

- Parameters:
  game_world - Current world
  x, y – Coordinate of the cell

- Returns:
  all neighbors of a cell in (x, y).

### How to implement the rules

#### Colorised Rule

The live cells have two different colors, red and blue. When a cell is born, it takes on the colour value of the majority of its three neighbours.

Since the birth of a cell is only happened when the number of its neighbors alive is 3 and we only have 2 colors, so you don't worry about the case that there are more than two cells with the same color in the neighborhood of a new cell. The new cell will always take on the color of the majority of its neighbors.

- Please note that it should be implemented as `class LifeRuleColorised`.

##### Hint

You may want to inherit `LifeRuleBase` and override its `DetermineNextState`.

#### LifeRuleExtended

The extended rule is a variant of the original game where the size of a cell's neighborhood is extended to include cells with a distance of 2, (i.e all 24 cells in a grid of 5 \* 5 are now its neighbor).

##### Hint

This can be done by override `GetNeighbors`.

#### LifeRuleWeighted

The weighted life rule is a variant of the original game where the size of a cell's neighborhood is extended to include cells with a distance of 2, (i.e all 24 cells in a grid of 5 \* 5 are now its neighbor). However，some neighbors might make more influence. i.e:

1. For a live cell, calculate the sum of the weights of its neighbor.

2. Any live cell with weight fewer than 4 dies, as if caused by under-population.

3. Any live cell with weight of 4, 5, 6 live neighbours lives on to the next generation.

4. Any live cell with weight more than 6 live neighbours dies, as if by over-population.

5. Any dead cell with exactly 6 live neighbours becomes a live cell, as if by reproduction.

The weights of a cell X's neighbor can be described as the following matrix:

```
1 1 2 1 1
1 2 2 2 1
2 2 X 2 2
1 2 2 2 1
1 1 2 1 1
```

##### Hint

This can be done by override `DetermineNextState` in `LifeRuleExtended`.

#### LifeRuleGenerations

The generations rule is a variant of the original game where the live cells would not dead immediately when overpopulated or underpopulated. Instead, the cells 'get older' before eventually dying.

The following are the rules:

1.  A cell in state 0 ("dead") will advance to state 1 ("get born") in the next generation of the pattern if the number of neighbors in state 1 ("live") in its Moore neighbourhood is present in the rule's birth conditions (Bx).
2.  A cell in state 1 ("live") will:

    - Remain in state 1 ("survive") in the next generation of the pattern if the number of neighbors in state 1 ("live") in its Moore neighborhood is present in the rule's survival conditions (Sx).
    - Advance to state 2 ("age") in the next generation of the pattern otherwise.

3.  A cell in state m ≥ 2 will advance to state m + 1 in the next generation of the pattern. In particular, a cell in state N will reset to state 0 ("die").

In our game, $N = 8$.

##### Hint

You may want to inherit `LifeRuleBase` and override its `DetermineNextState`.

### How to run

#### Compile the project

```bash
g++ -Wall -Wextra -o gof GameWorld.cpp GameManager.cpp LifeCell.cpp main.cpp LifeRuleStudent.cpp
```

#### Run the project

```bash
./gof <rule>
```

The program takes one argument, which is the rule you want to use. The rule can be `Base`, `Colorised`, `Extended`, `Weighted`, `Generations`.

Try to run with `./gof Base` and you can play with the original Game of Life.

### File Structure

The code for this project consists of several files, some of which you will need to read and understand in order to complete the assignment, and some of which you can ignore.

## Submission
