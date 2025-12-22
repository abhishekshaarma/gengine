#pragma once
#include <glm/glm.hpp>
#include "Maze.h"
#include "data.h"

// Collision against maze walls using same logic as your earlier canMove
inline bool canMove(float nx, float nz, const Maze& maze)
{
    const float R = 0.15f;   // collision radius

    int r = (int)nz;
    int c = (int)nx;

    // out of bounds
    if (r < 0 || c < 0 || r >= maze.size || c >= maze.size)
        return false;

    // Current cell walls
    if (maze.N[r][c])
    {
        float wallZ = r;
        if (nz < wallZ + R) return false;
    }
    if (maze.S[r][c])
    {
        float wallZ = r + 1;
        if (nz > wallZ - R) return false;
    }
    if (maze.W[r][c])
    {
        float wallX = c;
        if (nx < wallX + R) return false;
    }
    if (maze.E[r][c])
    {
        float wallX = c + 1;
        if (nx > wallX - R) return false;
    }

    // Neighbor cells' walls (shared edges)
    if (r > 0 && maze.S[r-1][c])
    {
        float wallZ = r;
        if (nz < wallZ + R) return false;
    }
    if (r < maze.size-1 && maze.N[r+1][c])
    {
        float wallZ = r + 1;
        if (nz > wallZ - R) return false;
    }
    if (c > 0 && maze.E[r][c-1])
    {
        float wallX = c;
        if (nx < wallX + R) return false;
    }
    if (c < maze.size-1 && maze.W[r][c+1])
    {
        float wallX = c + 1;
        if (nx > wallX - R) return false;
    }

    return true;
}

inline void movePlayerForward(Player& p, const Maze& maze)
{
    float nx = p.pos.x + sin(p.angle) * p.moveSpeed;
    float nz = p.pos.z + cos(p.angle) * p.moveSpeed;
    if (canMove(nx, nz, maze))
    {
        p.pos.x = nx;
        p.pos.z = nz;
    }
}

inline void movePlayerBackward(Player& p, const Maze& maze)
{
    float nx = p.pos.x - sin(p.angle) * p.moveSpeed;
    float nz = p.pos.z - cos(p.angle) * p.moveSpeed;
    if (canMove(nx, nz, maze))
    {
        p.pos.x = nx;
        p.pos.z = nz;
    }
}

inline void strafePlayerLeft(Player& p, const Maze& maze)
{
    float nx = p.pos.x - cos(p.angle) * p.moveSpeed;
    float nz = p.pos.z + sin(p.angle) * p.moveSpeed;
    if (canMove(nx, nz, maze))
    {
        p.pos.x = nx;
        p.pos.z = nz;
    }
}

inline void strafePlayerRight(Player& p, const Maze& maze)
{
    float nx = p.pos.x + cos(p.angle) * p.moveSpeed;
    float nz = p.pos.z - sin(p.angle) * p.moveSpeed;
    if (canMove(nx, nz, maze))
    {
        p.pos.x = nx;
        p.pos.z = nz;
    }
}

inline void turnPlayerLeft(Player& p)
{
    p.angle -= p.turnSpeed;
}

inline void turnPlayerRight(Player& p)
{
    p.angle += p.turnSpeed;
}
