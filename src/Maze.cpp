#include "Maze.h"
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>


void Maze::generate()
{
    // visited array
    std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));

    // RNG for shuffling directions
    std::mt19937 rng((unsigned)time(nullptr));

    // Pick random start cell
    int r = rng() % size;
    int c = rng() % size;

    // Stack for DFS
    std::stack<std::pair<int,int>> stk;
    stk.push({r, c});
    visited[r][c] = true;

    while (!stk.empty())
    {
        auto [cr, cc] = stk.top();

        // Order of directions will be randomized each iteration
        std::vector<std::pair<int,int>> dirs = {
            {0, 1},   // East
            {1, 0},   // South
            {0, -1},  // West
            {-1, 0}   // North
        };
        std::shuffle(dirs.begin(), dirs.end(), rng);

        bool moved = false;

        // Try all 4 directions
        for (auto &d : dirs)
        {
            int nr = cr + d.first;
            int nc = cc + d.second;

            // bounds check
            if (nr < 0 || nr >= size || nc < 0 || nc >= size)
                continue;

            // already visited
            if (visited[nr][nc])
                continue;

            // ---- Remove walls between current cell and neighbor ----
            if (nr == cr && nc == cc + 1) { // East
                E[cr][cc] = false;
                W[nr][nc] = false;
            }
            else if (nr == cr && nc == cc - 1) { // West
                W[cr][cc] = false;
                E[nr][nc] = false;
            }
            else if (nr == cr + 1 && nc == cc) { // South
                S[cr][cc] = false;
                N[nr][nc] = false;
            }
            else if (nr == cr - 1 && nc == cc) { // North
                N[cr][cc] = false;
                S[nr][nc] = false;
            }

            // mark visited and continue DFS
            visited[nr][nc] = true;
            stk.push({nr, nc});
            moved = true;
            break;
        }

        // If no moves available, backtrack
        if (!moved)
            stk.pop();
    }
}
bool Maze::hasWall(int r, int c, int dir) const
{
    switch (dir)
    {
        case 0: return N[r][c]; // North
        case 1: return E[r][c]; // East
        case 2: return S[r][c]; // South
        case 3: return W[r][c]; // West
    }
    return true;
}
