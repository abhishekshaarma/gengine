#pragma once
#include <vector>
#include <queue>
#include "Maze.h"
#include "data.h"

inline std::vector<std::vector<bool>> visible;

inline void computeVisibilityBFS(const Maze& maze, const Player& player)
{
    int N = maze.size;
    visible.assign(N, std::vector<bool>(N, false));

    int sr = (int)player.pos.z;
    int sc = (int)player.pos.x;

    if (sr < 0 || sc < 0 || sr >= N || sc >= N)
        return;

    // Normalize direction to {-1,0,1} grid direction
    float a = player.angle;
    int facing_r = 0;
    int facing_c = 0;

    float dx = sin(a);
    float dz = cos(a);

    /*
      Facing      forward(fr, fc)
      
      North       (-1, 0 ) 
      South       (+1, 0 )
      East         (0, +1)
      West         (0 , -1)

      WEST (0 , -1)
      EAST (0 , 1)
     mak 
    */

    
    if (fabs(dx) > fabs(dz))
        facing_c = (dx > 0 ? 1 : -1);
    else
        facing_r = (dz > 0 ? 1 : -1);

    std::queue<std::pair<int,int>> q;
    q.push({sr, sc});
    visible[sr][sc] = true;

    while (!q.empty())
    {
        auto [r, c] = q.front();
        q.pop();


        // forward = facing_r, facing_c
        int fr = r + facing_r;
        int fc = c + facing_c;

        // left = rotate (facing_r,facing_c) 90 degrees
        int lr = r + (-facing_c);
        int lc = c + (facing_r);

        // right = rotate 90 degrees other direction
        int rr = r + (facing_c);
        int rc = c + (-facing_r);


        auto tryAdd = [&](int nr, int nc, int from_r, int from_c)
        {
            if (nr < 0 || nc < 0 || nr >= N || nc >= N) return;

            // Check if wall blocks entry
            if (nr == from_r - 1 && maze.N[from_r][from_c]) return;
            if (nr == from_r + 1 && maze.S[from_r][from_c]) return;
            if (nc == from_c - 1 && maze.W[from_r][from_c]) return;
            if (nc == from_c + 1 && maze.E[from_r][from_c]) return;

            if (!visible[nr][nc])
            {
                visible[nr][nc] = true;
                q.push({nr, nc});
            }
        };

        tryAdd(fr, fc, r, c);
        tryAdd(lr, lc, r, c);
        tryAdd(rr, rc, r, c);
    }
}
