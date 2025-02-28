# Stack-Solitaire-Solver
### A C console-application that tries to solve a specific kind of solitaire card game

## The basic gameplay of the game that is being solved
1. shuffle a standard 32 card piquet deck
2. deal the cards out face down in 8 piles of four cards each
3. turn over the top cards of each pile
4. if no two face-up cards have the same face value you lost the game
5. else remove a pair (exactly two) face-up cards of the same face value
6. turn over uncovered face-down cards
7. if no more cards are left you won else jump to 4.

## How the solution is found
The implementation of the solution uses a recursive approach to determine whether or not a randomized game is solvable
