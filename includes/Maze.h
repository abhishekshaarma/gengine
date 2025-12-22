#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <random>

class Maze
{
public:
    int size;   // n x n maze

    std::vector<std::vector<bool>> N, E, S, W;


    void generate();  
    bool hasWall(int r, int c, int dir) const; // 0=N,1=E,2=S,3=W

    Maze(int n)
        : size(n),
          N(n, std::vector<bool>(n, true)),
          E(n, std::vector<bool>(n, true)),
          S(n, std::vector<bool>(n, true)),
          W(n, std::vector<bool>(n, true))
    {
    }

};

#endif
