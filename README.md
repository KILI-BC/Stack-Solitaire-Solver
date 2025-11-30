# Stack-Solitaire-Solver
### A C89 console-application that finds out how often a specific kind of solitaire card game has a valid solution

## The basic gameplay of the game that is being solved
1. shuffle a standard 32 card piquet deck
2. deal the cards out face down in 8 piles of four cards each
3. turn over the top cards of each pile
4. if no two face-up cards have the same face value you lost the game
5. else remove a pair (exactly two) face-up cards of the same face value
6. turn over the uncovered face-down cards
7. if no more cards are left you won else jump to 4.

## How a possible solution is found
The program implements a depth-first-search over all possible moves to determine whether or not a randomized game is solvable
